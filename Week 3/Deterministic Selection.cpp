#include<iostream>
#include<cstdio>
using namespace std;

int Partition(int arr[],int lower,int upper){
    int pivot=arr[lower],i=lower+1,j=lower+1;
    for(;j<=upper;j++){
            if(arr[j]<pivot){
                 int temp=arr[i];
                 arr[i]=arr[j];
                 arr[j]=temp;
                 i++;
            }
    }
    int temp=arr[lower];
    arr[lower]=arr[i-1];
    arr[i-1]=temp;
    /*for(int i=0;i<sz;i++) printf("%d ",arr[i]);
    cout<<endl;
    system("pause");
    */
    return (i-1);//returns partition index or final index of pivot after swap
}

int new_sort(
int DSelect(int arr[],int lower,int upper,int statistic){
    new_sort(arr);
    
int main()
{
    int sz,statistic
    scanf("%d",&sz);
    int arr[sz];
    cout<<"Enter Statistic to Search : ";
    scanf("%d",&statistic);
    for(int i=0;i<sz;i++) scanf("%d",&arr[i]);
    cout<<statistic<<"th order statistic = "<<DSelect(arr,0,sz-1,statistic)<<endl;
    //for(int i=0;i<sz;i++) printf("%d ",arr[i]);
    system("pause");
    return 0;
}
