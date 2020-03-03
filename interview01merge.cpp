//
// Created by anranzhai on 2020/3/3.
//
#include <vector>
#include <algorithm>
//直接合并后排序
void merge(std::vector<int>& A, int m, std::vector<int>& B, int n) {
    for(int i=0;i<n;i++){
        A[m+i]=B[i];
    }
    std::sort(A.begin(),A.end());
}

//双指针：正向双指针需要借助m+n大的数组空间，逆向双指针可以原地修改
void mergeDoublePointer(std::vector<int>& A, int m, std::vector<int>& B, int n) {
    if(n==0)
        return;
    if(m==0)
        A=B;
    int i=m-1,j=n-1,k=m+n-1;
    for(;i>=0&&j>=0;){
        if(A[i]==B[j]){
            A[k--]=A[i--];
            A[k--]=B[j--];
        } else if(A[i]>B[j])
            A[k--]=A[i--];
        else
            A[k--]=B[j--];
    }
    while(i>=0)
        A[k--]=A[i--];
    while(j>=0)
        A[k--]=A[j--];
}

int main(){
    mergeDoublePointer(,1);
}