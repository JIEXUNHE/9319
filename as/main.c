//
//  main.c
//  as
//
//  Created by 何杰逊 on 2019/8/7.
//  Copyright © 2019 何杰逊. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <assert.h>
typedef unsigned char byte;
int *ctable;
int *count;
int *occ;
int *b_prime;
int **map_occ;

void bsort(char *a, int l, char *b)//a为数组地址，l为数组长度。
{
    int i, j;
    int v,k;
    //排序主体
    for(i = 0; i < l - 1; i ++)
        for(j = i+1; j < l; j ++)
        {
            if(a[i] > a[j])//如前面的比后面的大，则交换。
            {
                v = a[i];
                k = b[i];
                a[i] = a[j];
                b[i] = b[j];
                a[j] = v;
                b[j] = k;
            }
        }
}






int transfer(int x)
{
    int p=1,y=0,yushu;
    while(1)
    {
        yushu=x%2;
        x/=2;
        y+=yushu*p;
        p*=10;
        if(x<2)
        {
            y+=x*p;
            break;
        }
    }
    return y;
}
void number(int x ,int size,int *num){
    
    int i;
    
    for (i = 0;i <=7;i++)
        
    {
        num[7-i] = x%10;
        x=x/10;
        
    }
}
char* delet_last(char * filename)
{
    int index=0;
    
    int length=0;
    length = strlen(filename);
    char *name;
    for(index=0;index<length-4;index++){
        name[index]= filename[index];
    }
    return name;
}
void sort(char *a, int l)//a为数组地址，l为数组长度。
{
    int i, j;
    int v;
    //排序主体
    for(i = 0; i < l - 1; i ++)
        for(j = i+1; j < l; j ++)
        {
            if(a[i] > a[j])//如前面的比后面的大，则交换。
            {
                v = a[i];
                a[i] = a[j];
                a[j] = v;
            }
        }
}
char* my_strrchr(char *str,int ch)
{
    
    int len=strlen(str);
    char *right=str+len-1;
    assert(str!=NULL);
    while(right>=str)
    {
        if(*right==ch)
            return  right;
        right--;
    }
    return NULL;
}
void create_b_prime(char *a, int l, char *b){
    int i, j;
    int v,k;
    //排序主体
    //printf("%s\n",a);
    for(i = 0; i < l - 1; i ++)
        for(j = i+1; j < l; j ++)
        {
            if(a[i] > a[j])//如前面的比后面的大，则交换。
            {
                v = a[i];
                k = b[i];
                a[i] = a[j];
                b[i] = b[j];
                a[j] = v;
                b[j] = k;
            }
        }
    
    
}
void create_occ(char* bwt){
    int len =strlen(bwt);
    char s[len];
    occ = calloc(len,sizeof(int));
    s[0]=bwt[0];
    occ[0]=0;
    int c1,c2;
    for(int i=1;i<strlen(bwt);i++){
        int count=0;
        for(int j=i-1;j>=0;j--){
            
            c1=bwt[i];
            
            c2=bwt[j];
            if(c1==c2){
                count++;
                occ[i]=count;
            }else{
                occ[i]=count;
            }
        }
        
    }
    
    
}
void create_ctable(char * s,int **b ,int size){
    
    int i,j=0;
    char bwt[(size*8)-1];
    int bwt_pos=0;
    
    for(i=0;i<size;i++){
        for(int m=0;m<8;m++){
            //printf("%d",b[i][m]);
            if(i==0&&m==0){
                bwt[0]=s[0];
                bwt_pos++;
            }else{
                if(b[i][m]==1){
                    j=j+1;
                    bwt[bwt_pos] = s[j];
                    bwt_pos++;
                }
                else{
                    bwt[bwt_pos] = s[j];
                    bwt_pos++;
                }
            }
        }
    }
    bwt[(size*8)-1]='\0';
    
    
    
    //printf("\n%s\n",bwt);
    int bwt_len=strlen(bwt);
    create_occ(bwt);
    char first_col[bwt_len];
    for(i=0;i<strlen(bwt);i++){
        first_col[i]=bwt[i];
    }
    ctable = calloc(127,sizeof(int));
    count = calloc(127,sizeof(int));
    sort(first_col,bwt_len);
    //printf("\n%s\n",first_col);
    int c_pos=0;
    ctable[0]=first_col[0];
    count[c_pos]=0;
    int c1,c2;
    for(int i=1;i<strlen(first_col);){
        
        c1 = ctable[c_pos];
        c2 = first_col[i];
        if(c1==c2){
            i++;
        }else{
            c_pos++;
            count[c_pos]=i;
            
            ctable[c_pos] = first_col[i];
            i++;
        }
        
    }/*
      printf("\n----------count-----------\n");
      printf("%d,%d\n",0,count[0]);
      for(i = 0;i<127;i++){
      if(count[i])printf("%d,%d\n",i,count[i]);
      }
      
      printf("\n----------ctable-----------\n");
      
      for(i = 0;i<127;i++){
      if(ctable[i])printf("%d: %c\n",i,ctable[i]);
      }*/
    map_occ =calloc(bwt_len,sizeof(int *));
    for(int i=0;i<bwt_len;i++){
        *(map_occ+i) = calloc(c_pos,sizeof(int));
    }
    //int map_occ[bwt_len][c_pos];
    for(int i=0;i<bwt_len;i++){
        for(int j=0;j<=c_pos;j++){
            map_occ[i][j]=0;}}
    for(int i=0;i<bwt_len-1;i++){
        for(int j=0;j<=c_pos;j++){
            if(i==0){
                map_occ[i][j]=0;
            }
            if(ctable[j]==bwt[i]){
                map_occ[i+1][j]=map_occ[i][j]+1;
            }else{
                map_occ[i+1][j]=map_occ[i][j];
            }
            
        }
    }
    
    /*
     printf("  ");
     for(int j=0;j<=c_pos;j++){
     printf("%c ",ctable[j]);
     }
     for(int i=0;i<bwt_len;i++){
     printf("\n%d",i);
     for(int j=0;j<=c_pos;j++){
     printf(" %d",map_occ[i][j]);
     }
     }
     */
    int len=(size*8)-1;
    char s_table[len];
    int index=0;
    for(int i=0;i<size;i++){
        for(int j=0;j<8;j++){
            s_table[index]=b[i][j];
            index=index+1;
        }
    }
    //printf("%s\n",first_col);
    char a[index];
    char d[index];
    d[0]=bwt[0];
    a[0]=1;
    int b_position=1;
    int s_position=0;
    int d1,d2;
    while(b_position<index){
        d1=d[s_position];
        d2=bwt[b_position];
        //result = my_strrchr(s,bwt_arr[b_position]);
        if(d1==d2){
            a[b_position]=0;
            b_position++;
        }else{
            s_position++;
            d[s_position]=bwt[b_position];
            a[b_position]=1;
            b_position++;
        }
    }
    int b_len=0;
    for(int i=0;i<b_position;i++){
        b_len++;
    }
    char *b_prime=a;
    create_b_prime(bwt,b_len,b_prime);
    
    for(int i=0;i<b_len;i++){
        printf("%d",b_prime[i]);
    }
    printf("\n");
    
}


int main(int argc, char **argv){
    char *s =argv[1];
    char * filename;
    filename = argv[2];
    
    int pathlen = strlen(argv[2]);
    //printf("%d\n",pathlen+1);
    char s_name[pathlen+2];
    for(int i=0;i<pathlen;i++){
        s_name[i]= filename[i];
    }
    s_name[pathlen] ='.';
    s_name[pathlen+1] ='s';
    s_name[pathlen+2] = '\0';
    //printf("%s\n",s_name);
    //char *p = argv[0];
    FILE *fp3 = fopen("op.txt","w");
    
    fprintf(fp3,"%s",s);
    //free(fp);
    fclose(fp3);
    FILE *fp1 = fopen(s_name,"r");//fp1 for bwt .s .b
    
    fseek(fp1, 0, SEEK_END); // seek to end of file
    int size1 = ftell(fp1); // get current file pointer
    fseek(fp1, 0, SEEK_SET);
    char data1[size1];
    
    
    fread(data1,sizeof(char),size1 ,fp1);
    //printf("%s\n",data1);
    fclose(fp1);
    
    filename = argv[2];
    //printf("%d\n",pathlen+1);
    char b_name[pathlen+2];
    for(int i=0;i<pathlen;i++){
        b_name[i]= filename[i];
    }
    b_name[pathlen] ='.';
    b_name[pathlen+1] ='b';
    b_name[pathlen+2] = '\0';
    //printf("%s\n",b_name);
    FILE *fp2 = fopen(b_name,"rb");//fp1 for bwt .s .b
    
    fseek(fp2, 0, SEEK_END); // seek to end of file
    int size2 = ftell(fp2); // get current file pointer
    fseek(fp1, 0, SEEK_SET);
    unsigned char data2[size2];
    
    int bwt[size2];
    for(int index=0;index<size2*8;){
        fread(data2,sizeof(byte),8 ,fp2);
        
        index++;
    }
    
    
    for(int i=0;i<size2;i++){
        bwt[i] = transfer(data2[i]);
        //printf("%d",bwt[i]);
    }
    int **num;
    for(int i=0;i<size2;i++){
        
        number(bwt[i],size2,num[i]);
    }
    create_ctable(data1,num,size2);
    fclose(fp2);
}
