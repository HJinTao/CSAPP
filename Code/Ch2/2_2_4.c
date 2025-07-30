#include<stdio.h>

int main(){
    short int v = -12345;
    unsigned short uv = (unsigned short)v;   // 强制类型转换的结果保持位值不变，只是改变了解释这些位的方式 
    printf("v = %d, uv = %u\n", v, uv);  
    int x = -1;    // 0xFFFFFFFF 
    printf("sizeof int = %ld\n",sizeof(int));
    printf("sizeof short = %ld\n",sizeof(short));
    printf("x = %u = %d\n",x,x);
}