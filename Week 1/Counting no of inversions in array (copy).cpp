//It uses Merge Sort

#include<iostream>
#include<cstdio>
using namespace std;
#define INF 10000000
int arr[10000];
int count_split_inversions(int p,int q,int r){
    int n1=q-p+1 , n2=r-q;
    int L[n1+1],R[n2+1];
    for(int i=0;i<n1;i++) L[i]=arr[p+i];
    for(int i=0;i<n2;i++) R[i]=arr[q+1+i];
    L[n1]=R[n2]=INF;
    int count=0,x=0,y=0;
    for(int k=p;k<=r;k++){
            if(L[x]<=R[y]) arr[k]=L[x++];
            else{
                 arr[k]=R[y++];
                 count+=(n1-x);
            }
    }
    return count;
}
int count_inversions(int a,int b){
    if(b-a<=0) return 0;
    else{
         int c=(a+b)/2;
         int x=count_inversions(a,c);
         int y=count_inversions(c+1,b);
         int z=count_split_inversions(a,c,b);
         return x+y+z;
    }
}
int main()
{
    int sz;
    scanf("%d",&sz);
    for(int i=0;i<sz;i++) scanf("%d",&arr[i]);
    cout<<count_inversions(0,sz-1)<<endl;
    system("pause");
    return 0;
}
