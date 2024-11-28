#include<iostream>
using namespace std;
void merge(int arr[],int p ,int mid ,int q){
    int n1 = mid-p+1;
    int n2 = q-mid;
    int a1[n1];
    int a2[n2];
    for (int i {0};i<n1;i++){
        a1[i] = arr[p+i];}
    for (int i {0};i<n2;i++){
        a2[i] = arr[mid+i+1];}
    int i=0;
    int j=0;
    int k=p;
    while(i<n1 && j<n2){
        if(a1[i]<a2[j]){
            arr[k] = a1[i];
            i++;
            k++;
        }
        else{
            arr[k] = a2[j];
            j++;
            k++;}
    }
    while(i<n1){
        arr[k] = a1[i];
        i++;
        k++;}
    while(j<n2){
        arr[k] = a2[j];
        j++;
        k++;}}
void mergesort(int arr[],int l , int r){
    if (l<r){
        int mid = (l+r)/2;
        mergesort(arr,l,mid);
        mergesort(arr,mid+1,r);
        merge(arr,l,mid,r);}}
int main(){   
    int arr[] = {2,1,33,4,22};
    int Numberofelement = sizeof(arr)/sizeof(arr[0]);
    mergesort(arr,0,Numberofelement-1);
    cout<<"Sorting the array using Mergesort"<<endl;
    for (int i =0;i<Numberofelement;i++){
        cout<<arr[i]<<" ";}
    return 0;
}