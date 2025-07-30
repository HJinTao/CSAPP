#include "functions.h"

int main(){

    short sx = -12345;
    unsigned short usx = sx;
    int x = sx;
    unsigned int ux = usx;
    printf("sx = %d:\t",sx);
    show_bytes((byte_pointer)&sx, sizeof(sx));
    
}