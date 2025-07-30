#include<stdio.h>
#include<string.h>
/*
    typeof(unsigned char) == 1
    用unsigned char(0x00-0xFF)而不是char是因为char可能是有符号(-128-127)的或无符号的
*/
typedef unsigned char *byte_pointer; 
void show_bytes(byte_pointer start, size_t len){
    size_t i;
    for (i = 0; i < len; i++) {
        printf(" %.2x", start[i]);
    }
    printf("\n");
}

void show_int(int x) {
    show_bytes((byte_pointer)&x, sizeof(int));   //这里的强制类型转换不会改变真实的指针
                                                //只是告诉编译器以新的数据类型来看待被指向的数据
}

void show_float(float x) {
    show_bytes((byte_pointer)&x, sizeof(float));
}

void show_pointer(void *x) {
    show_bytes((byte_pointer)&x, sizeof(void *));
}

void inplace_swap(int *x, int *y) {
    *y = *x ^ *y;
    *x = *x ^ *y;
    *y = *x ^ *y;
}

void reverse_array(int arr[],int cnt){
    int first = 0, last = cnt - 1;
    for(;first < last;first++,last--){
        inplace_swap(&arr[first], &arr[last]);
    }
    // int temp = -3;
    // for(;temp <= 0 && printf("x1\n");temp++,printf("x2\n")){
    //     printf("x3\n");
    // }
}

int bis(int x,int m){
    // 将m为1的每个位置上，将x的对应位更改为1,等价于 |
    return x | m;
}

int bic(int x,int m){
    // 将m为1的每个位置上，将x的对应位更改为0
    return x & ~m;
}

int bool_or(int x,int y){
    return bis(x,y);
}

int bool_xor(int x,int y){
    // 使用了主析取范式
    return bis(bic(x,y), bic(y,x));
}

int main(){
    int a = 12345;
    float b = 3.14;
    int *p = &a;
    char *x = "12345";
    printf("Integer representation: ");
    show_int(a);
    
    printf("Float representation: ");
    show_float(b);
    
    printf("Pointer representation: ");
    show_pointer(p);

    printf("String representation: ");
    show_bytes((byte_pointer)x, strlen(x) + 1);  // 显示字符串(包括终止符)
    // printf("%ld\n",sizeof(unsigned char));
    return 0;
}