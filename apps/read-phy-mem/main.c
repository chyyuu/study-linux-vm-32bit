#define _FILE_OFFSET_BITS 64
#define _LARGEFILE64_SOURCE

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>




typedef unsigned short  u16;
typedef signed short    s16;
typedef int             s32;
typedef unsigned int    u32;
typedef unsigned int    uint32;
typedef unsigned long long u64;



uint32 utl_str2int(void *str)
{
    uint32 rst=0;
    uint32  i,tmp=0,len;
    uint32 sign,val;
    char *ptr = str;

    len = strlen((char *)ptr);
    if((ptr[1]=='x')||(ptr[1]=='X')){//HEX
        ptr +=2;
        for (i=2;i<len;i++) {
            tmp = *ptr++;
            if ((tmp<='9') && (tmp>='0')) {
                tmp = tmp -'0';
                rst = (rst<<4) + tmp;
            }
            else if ((tmp<='F') && (tmp>='A')) {
                tmp = tmp -'A' + 10;
                rst = (rst<<4) + tmp;
            }
            else if ((tmp<='f') && (tmp>='a')) {
                tmp = tmp -'a' + 10;
                rst = (rst<<4) + tmp;
            }
            else break;
            //rst = (rst<<4) + tmp;
        }
        return rst;
    }
    else{
        for (i = 0;; i++) {
            if (ptr[i] != ' ') {
                break;
            }
        }
        sign = (ptr[i] == '-' ?  - 1: 1);
        if (ptr[i] == '+' || ptr[i] == '-') {
            i++;
        }
        for (val = 0;; i++) {
            if (ptr[i] >= '0' && ptr[i] <= '9') {
                val = 10 * val + (ptr[i] - '0');
            } else {
                break;
            }
        }
        return  sign*val;
    }
}



int main(int argc, char *argv[])
{
    if(argc != 3){
        printf("args invalid\n");
        return 0;
    }

    u32 addr = utl_str2int(argv[1]);
    u32 size = utl_str2int(argv[2]);

    printf("read from 0x%08X, size %d\n", addr, size);


    int fd = open("/dev/phy_mem", O_RDONLY);
    if(fd < 0){
        printf("phy_mem open fail\n");
        return 0;
    }

    addr = addr & 0xFFFFFFF8;
    if(size > 256){
        size = 256;
    }
    size = (size + 8) & 0xFFFFFFF8;

    int ret = lseek64(fd, addr, SEEK_SET);
    printf("lseek64: addr:%08x, ret: %d, errno:%d\n", addr, ret, errno);

    char buf[256];
    int read_size = read(fd, buf, size);
    if(read_size < 0){
        printf("read failed\n");
        return 0;
    }

    u64 *p = (u64*)buf;

    int i;
    for(i = 0; i< 16; i++){
        printf("%2d: %016llX\n", i, *(p+i));
    }










    return 0;
}



