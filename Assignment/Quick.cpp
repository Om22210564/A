#include<iostream>
using namespace std;
void swap(int arr[],int a ,int b){
    int temp = arr[a];
    arr[a] = arr[b];
    arr[b] = temp;
}
int partition(int arr[],int l ,int r){
    int pivot =  arr[r];
    int i = l-1;
    for (int j = l;j<r; j++){
        if(arr[j]<pivot){
            i++;
            swap(arr,i,j);}}
    swap(arr,i+1,r);
    return i+1;
}
void quicksort(int arr[],int l,int r){
    if (l<r){
        int pi = partition(arr,l,r);
        quicksort(arr,l,pi-1);
        quicksort(arr,pi+1,r);}
}
int main(){   
    int arr[] = {2,1,33,4,22};
    int Numberofelement = sizeof(arr)/sizeof(arr[0]);
    quicksort(arr,0,Numberofelement-1);
    cout<<"Sorting the array using Quicksort"<<endl;
    for (int i =0;i<Numberofelement;i++){
        cout<<arr[i]<<" ";
    }
    return 0;
}