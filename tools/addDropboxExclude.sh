#!/bin/bash

#traversal rules in .gitignore file
while read LINE
do 
    #ignore empty line
    if [ -n "$LINE" ];then
        #line include "#" is comment
        if [[ $LINE != *"#"* ]]
        then
            files=($(find -name $LINE ))

            #file lists
            for file in "${files[@]}"; do
                cmd="dropbox exclude add $file"
                eval "$cmd" 
            done
        fi
    fi
done < .gitignore
