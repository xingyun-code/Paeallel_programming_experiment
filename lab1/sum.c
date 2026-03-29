#define _GNU_SOURCE//ai告诉我的宏定义？和linux系统有关
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double timecount() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);//CLOCK_为单调时钟
    return ts.tv_sec + ts.tv_nsec * 1e-9;
}//使用纳秒精度的时钟计时

double pingfan(double *in,int n){
    double sum=0.0;
    for(int i=0;i<n;i++){
        sum+=in[i];
    }
    return sum;
}//采用最简单的直接累加

double jiandan(double *in,int n){
    double sum1=0.0;
    double sum2=0.0;
    for(int i=0;i<n;i+=2){
        sum1+=in[i];
        sum2+=in[i+1];
    }
    return sum1+sum2;
}
//采用两个计算并行的方法计算
double fenzhi(double *in,int n){
    if (n ==1){
        return in[0];
    }
    int mid = n/2;
    return fenzhi(in,mid)+fenzhi(in+mid,n-mid);
}
//采用分治递归进行实现
int main(){
    int n=10;
    int repeat =100000;
    double *in=(double*)malloc(n*sizeof(double));
    for(int i=0;i<n;i++){
        in[i]=1.0;
    }
    double start1 = timecount();
    for(int i=0;i<repeat;i++){
        double tmp = pingfan(in,n);
    }
    double end1 = timecount();
    double time1=end1-start1;
    double arrange1=time1/repeat;
    printf("平凡算法的总时间为：%f秒,单次平均时间为：%f秒",time1,arrange1);
    double start2 = timecount();
    for(int i=0;i<repeat;i++){
        double tmp = jiandan(in,n);
    }
    double end2 = timecount();
    double time2=end2-start2;
    double arrange2=time2/repeat;
    printf("简单优化算法的总时间为：%f秒,单次平均时间为：%f秒",time2,arrange2);
    double start3 = timecount();
    for(int i=0;i<repeat;i++){
        double tmp = fenzhi(in,n);
    }
    double end3 = timecount();
    double time3=end3-start3;
    double arrange3=time3/repeat;
    printf("分治算法的总时间为：%f秒,单次平均时间为：%f秒",time3,arrange3);
    free(in);
    return 0;
}