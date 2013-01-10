//ans : 162085 comparisons
//Problem : Find the ith smallest element in the given array.

#include<iostream>
#include<cstdio>
using namespace std;
int sz,statistic;
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
int comp=0;
int RSelect(int arr[],int lower,int upper,int statistic){
    if(lower<upper){
            int part=Partition(arr,lower,upper);
            /*cout<<"comps :"<<comp<<endl;
            system("pause");
            */
            if(statistic==part) return arr[part];
            else if(part>statistic) return RSelect(arr,lower,part-1,statistic);
            else return RSelect(arr,part+1,upper,statistic-part);
            comp+=upper-lower;
            //QuickSort(arr,lower,part-1);
            //QuickSort(arr,part+1,upper);
    }
    //return comp;
}
int main()
{
    scanf("%d",&sz);
    int arr[sz];
    cout<<"Enter Statistic to Search : ";
    scanf("%d",&statistic);
    for(int i=0;i<sz;i++) scanf("%d",&arr[i]);
    //cout<<"Comparisons :"<<RSelect(arr,0,sz-1,statistic)<<endl;
    cout<<statistic<<"th order statistic = "<<RSelect(arr,0,sz-1,statistic)<<endl;
    //for(int i=0;i<sz;i++) printf("%d ",arr[i]);
    system("pause");
    return 0;
}
/*e.g.
9
3
6 10 13 5 8 3 2 11 5
*/
