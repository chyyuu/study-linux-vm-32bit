#!/bin/bash

#traversal rules in .gitignore file
while read LINE
do 
    #ignore empty line
    if [ -n "$LINE" ];then
        #line include "#" is comment
        if [[ $LINE != *"#"* ]]
        then
            # wildcard * need to find 
            if [[ $LINE == *"*"* ]]
            then
                files=($(find -name $LINE ))

                #file lists
                for file in "${files[@]}"; do
                    cmd="dropbox exclude add $file"
                    eval "$cmd" 
                done
            else
                #specified file can't use command find
                #there may be file with samename
                cmd="dropbox exclude add $LINE"
                eval "$cmd" 
            fi  

        fi
    fi
done < .gitignore
