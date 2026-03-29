#define _GNU_SOURCE//AI说这是需要添加的宏定义？貌似和Linux系统有关系
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 1024//可以自主更改n值进行多次测试便于比较

double timecount() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);//CLOCK_为单调时钟
    return ts.tv_sec + ts.tv_nsec * 1e-9;
}//使用纳秒精度的时钟计时

void pingfan(double *Ju,double *a,double *result,int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            result[i]+=Ju[j*n+i]*a[j];
        }
    }
}

void cache(double *Ju,double *a,double *result,int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            result[j]+=Ju[i*n+j]*a[i];
        }
    }
}

int main(){
    int n=N;
    double *Ju=(double*)malloc(n*n*sizeof(double));
    double *a=(double*)malloc(n*sizeof(double));
    double *result1=(double*)calloc(n,sizeof(double));
    double *result2=(double*)calloc(n,sizeof(double));
    for(int i=0;i<n;i++){
        a[i]=1.0;
        for(int j=0;j<n;j++){
            Ju[i*n+j]=i+j;
        }
    }
    double start=get_time();
    pingfan(Ju,a,result1,n);
    double end = get_time();
    printf("平凡算法的时间需求为：",end-start);
    double start=get_time();
    cache(Ju,a,result2,n);
    double end = get_time();
    printf("优化算法的时间需求为：",end-start);
    free(Ju);
    free(a);
    free(result1);
    free(result2);
    return 0;
}