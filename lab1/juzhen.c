#define _GNU_SOURCE//ai告诉我的宏定义？和linux系统有关
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
    double start1=timecount();
    pingfan(Ju,a,result1,n);
    double end1 = timecount();
    printf("平凡算法的时间需求为：%f秒\n",end1-start1);
    double start2=timecount();
    cache(Ju,a,result2,n);
    double end2 = timecount();
    printf("优化算法的时间需求为：%f秒\n",end2-start2);
    free(Ju);
    free(a);
    free(result1);
    free(result2);
    return 0;
}