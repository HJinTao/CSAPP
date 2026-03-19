#include "cachelab.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#define USAGE_STR \
    "Usage: ./csim [-hv] -s <num> -E <num> -b <num> -t <file>\n" \
    "Options:\n" \
    "  -h         Print this help message.\n" \
    "  -v         Optional verbose flag.\n" \
    "  -s <num>   Number of set index bits.\n" \
    "  -E <num>   Number of lines per set.\n" \
    "  -b <num>   Number of block offset bits.\n" \
    "  -t <file>  Trace file.\n\n" \
    "Examples:\n" \
    "  linux>  ./csim-ref -s 4 -E 1 -b 4 -t traces/yi.trace\n" \
    "  linux>  ./csim-ref -v -s 8 -E 2 -b 4 -t traces/yi.trace\n"
typedef struct block
{
    unsigned long tag;
    char v;
    char lru;
}block;

typedef enum{
    MISS = 0,
    HIT = 1,
    EVICTION = 2
}STATUS;

block** memory;

int s,E,b;
int S;

int verbose = 0;

FILE* fp = NULL;

int miss = 0,hit = 0,eviction = 0;

char op;
unsigned long address;
int size;


void parse_args(int argc,char *argv[])
{
    int opt;
    while((opt = getopt(argc,argv,"s:E:b:t:hv")) != -1){
        switch (opt){
            case 'h':
                printf(USAGE_STR);
                break;
            case 'v':
                verbose = 1;
                break;
            case 's':
                s = atoi(optarg);
                break;
            case 'E':
                E = atoi(optarg);
                break;
            case 'b':
                b = atoi(optarg);
                break;
            case 't':
                fp = fopen(optarg,"r");
                break;
            case '?':
                printf("未知选项或缺少参数\n");
                break;
            default:
                break;
        }
    }
}

void init(){
    S = 1 << s;
    memory = (block**)calloc(S,sizeof(block*));
    for(int i = 0; i < S; i++){
        memory[i] = (block*)calloc(E,sizeof(block));
    }
}

void end(){
    fclose(fp);
    for(int i = 0; i < S; i++){
        free(memory[i]);
    }
    free(memory);
}

void print_status(STATUS status){
    printf("%c %lx,%d ",op,address,size);
    if(status == MISS){
        printf("miss");
    }
    else if(status == HIT){
        printf("hit");
    }
    else{
        printf("miss eviction");
    }
    printf("\n");
}

STATUS access(){
    unsigned long mask_s = (1UL << s) - 1;
    int add_s = (address >> b) & mask_s;
    unsigned long tag = address >> (s + b);  // 无符号数右移是逻辑右移
    block* p = memory[add_s];

    for(int i = 0; i < E; i++){
        p[i].lru++;
    }

    char is_full = 1;
    int lru_max_index = 0;
    int lru = p[0].lru;


    for(int i = 0; i < E; i++){
        if(p[i].v == 0){
            is_full = 0;
        }
        else if(p[i].v == 1){
            if(p[i].tag == tag){
                p[i].lru = 0;
                hit++;
                return HIT;
            }
            //找出最久未使用的块索引
            if(p[i].lru > lru){
                lru_max_index = i;
                lru = p[i].lru;
            }

        }
    }

    if(is_full == 1){
        p[lru_max_index].lru = 0;
        p[lru_max_index].tag = tag;
        p[lru_max_index].v = 1;
        miss++;
        eviction++;
        return EVICTION;
    }
    else{
        for(int i = 0; i < E; i++){
            if(p[i].v == 0){
                p[i].lru = 0;
                p[i].tag = tag;
                p[i].v = 1;
                miss++;
                return MISS;
            }
        }
    }
    return 0;
}

void load(){
    print_status(access());
}

void store(){
    print_status(access());
}

void modify(){
    load();
    store();
}




int main(int argc, char *argv[])
{
    parse_args(argc,argv);
    init();
    

    while(fscanf(fp," %c %lx,%d",&op,&address,&size) == 3){

        // printf("%x\n",add_s);
        if(op == 'I'){
            continue;
        }
        else if(op == 'M'){
            modify();
        }
        else if(op == 'L'){
            load();
        }
        else if(op == 'S'){
            store();
        }
    }
    printSummary(hit,miss,eviction);
    end();
    return 0;
}
