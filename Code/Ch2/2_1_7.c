#include<stdio.h>

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
    int a = 5, b = 10;
    printf("Before swap: a = %d, b = %d\n", a, b);
    inplace_swap(&a, &b);
    printf("After swap: a = %d, b = %d\n", a, b);
    int arr[] = {1, 2, 3, 4, 5};
    int cnt = sizeof(arr) / sizeof(arr[0]);
    printf("Original array: ");
    for(int i = 0; i < cnt; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    reverse_array(arr, cnt);
    printf("Reversed array: ");
    for(int i = 0; i < cnt; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}