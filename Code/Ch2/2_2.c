#include<stdio.h>

typedef unsigned char *byte_pointer; 

void show_bytes(byte_pointer start, size_t len){
    size_t i;
    for (i = 0; i < len; i++) {
        printf(" %.2x", start[i]);
    }
    printf("\n");
}

int main(){
    // short int v = -12345;
    // unsigned short uv = (unsigned short)v;   // 强制类型转换的结果保持位值不变，只是改变了解释这些位的方式 
    // printf("v = %d, uv = %u\n", v, uv);  
    // int x = -1;    // 0xFFFFFFFF 
    // printf("sizeof int = %ld\n",sizeof(int));
    // printf("sizeof short = %ld\n",sizeof(short));
    // printf("x = %u = %d\n",x,x);

    short sx = -12345;
    unsigned short usx = sx;
    int x = sx;
    unsigned int ux = usx;
    printf("sx = %d:\t",sx);
    show_bytes((byte_pointer)&sx, sizeof(sx));
}