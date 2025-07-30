#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include<stdio.h>

typedef unsigned char *byte_pointer; 
void show_bytes(unsigned char *start, size_t len);
void show_int(int x);
void show_float(float x);
void show_pointer(void *x);

#endif