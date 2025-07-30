#include<stdio.h>

int uadd_ok(unsigned x, unsigned y) {
    unsigned sum = x + y;
    return !(sum < x);  // 如果没有溢出，则返回1
}

int tadd_ok(int x,int y){
    int sum = x + y;
    return !((x > 0 && y > 0 && sum < 0) || (x < 0 && y < 0 && sum > 0)); // 如果没有溢出，则返回1
}

int main(){

}