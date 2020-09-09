//
//  main.c
//  lzw
//
//  Created by 何杰逊 on 2019/6/25.
//  Copyright © 2019 何杰逊. All rights reserved.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
struct DictNode {
    int index; // the position in the list
    int w; // w start from 256
    int k; //last byte
    struct DictNode *next;
};
void dicInit(void);
void appendNode(struct DictNode *node);
void dicDestroy(void);
int dicsearch(int w, int k);
int dicWW(int index);
int dicKK(int index);
void dicIncrese(int w, int k, int index);
struct DictNode *dic, *tail;
typedef struct{
    int w; // w 256
    int k; // current
} DictElement;
void dicArrayIncrese(int w, int k, int index);
int dicArrayWW(int index);
int dicArrayKK(int index);
enum {
    Size = 16384 , // maximum number
    codeLength = 14, // codes
    maxValue = Size - 1,
    empty = -1
};
DictElement dicArray[Size];
void dicInit() {
    int i;
    struct DictNode *node;
    for (i = 0; i < 256; i++) { // ASCII
        node = (struct DictNode *)malloc(sizeof(struct DictNode));
        node->w = empty;
        node->k = i;
        appendNode(node);
    }
}
void appendNode(struct DictNode *node) {
    if (dic != NULL) tail->next = node;
    else dic = node;
    tail = node;
    node->next = NULL;
}
void dicDestroy() {
    while (dic != NULL) {
        dic = dic->next; /* the head now links to the next element */
    }
}
int dicsearch(int w, int k) {
    struct DictNode *node;
    for (node = dic; node != NULL; node = node->next) { // ...traverse
        if (node->w == w && node->k == k) {
            return node->index;}
    }
    return empty;
}
int dicWW(int index) {
    struct DictNode *node;
    for (node = dic; node != NULL; node = node->next) { //traverse
        if (node->index == index) return node->w;
    }
    return -1;
}
int dicKK(int index) {
    struct DictNode *node;
    for (node = dic; node != NULL; node = node->next) { // same..da.da
        if (node->index == index) {
            //printf("\nNODE %c %c %c\n", nod
            return node->k;
        }
    }
    return -1;
}
void dicIncrese(int w, int k, int index) {
    struct DictNode *node;
    node = (struct DictNode *)malloc(sizeof(struct DictNode));
    node->index = index;
    node->w = w;
    node->k = k;
    printf("%c ",w);
    appendNode(node);
}
void compress(FILE *inputFile) {
    int w = getc(inputFile);
    if (w == EOF) {
        return;
    }
    
    int k;
    int nextCode;
    int index;
    nextCode = 256;
    dicInit();
    while ((k = getc(inputFile)) != (unsigned)EOF) {
        
        if ((index = dicsearch(w, k)) != -1){
            printf("%d",index);
            w = index;
        }
        else {
            
            if (nextCode < Size){
                dicIncrese(w, k, nextCode++);
            }
            
            w = k;
            
        }
    }


}
int main(int argc,char *argv[]){
    FILE *fp;
    char *filename;
    filename = argv[2];
    //filename = "test4.txt";
    fp = fopen(filename, "r");
    if(fp==NULL){
        puts("can't open the file!");
        exit(0);
    }
        compress(fp);

}

