#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unistd.h>

using namespace std;

int find_the_smallest_interval(vector<int> numbers);
int find_the_smallest_interval1(vector<int> numbers);

void mergeSort(int arr[],int l,int r);
void merge(int arr[], int l, int m, int r);

int main() {
    cout << "Hellow World"<<endl;
    vector<int> x = {1,6,11,8,2} ;

    int res = find_the_smallest_interval(x);

    cout << res << endl;
    
    res = find_the_smallest_interval1(x);

    cout << res << endl;

    return 0;
}

int find_the_smallest_interval(vector<int> numbers) {
    int smallest_int = 0xFFFFFFF;
    for (int i =0;i<numbers.size();i++){
        for (int j = 0;j<numbers.size();j++){
            // cout << smallest_int <<" ,"<< i << endl;
            if( i!=j && smallest_int > abs(numbers[i] - numbers[j]))
                smallest_int = abs(numbers[i] - numbers[j]);
        }
    }

    return smallest_int;
}

int find_the_smallest_interval1(vector<int> numbers) {
    
    //quick sort sort [1,2,4,6,8]
    int n = numbers.size();
    int arr[n];

    for (int i = 0; i < n; i++) {
        arr[i] = numbers[i];
    }

    mergeSort(arr, 0, (n ));

    
    for (int i = 0; i < n; i++) {
        arr[i] = arr[i+1] - arr[i];
    }
    
    int smallest=0xFFFFFFF;

    for (int i = 0; i < n-1; i++) {
        if(smallest > arr[i])
            smallest = arr[i];
    }

    return smallest;
}

void merge(int arr[], int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;
 
 
    int L[n1], R[n2];
 
   
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

 
    int i = 0;
 
    
    int j = 0;
 
    
    int k = l;
 
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
  
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
 
   
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
 

void mergeSort(int arr[],int l,int r){
    if(l>=r){
        return;
    }
    int m = (l+r-1)/2;
    mergeSort(arr,l,m);
    mergeSort(arr,m+1,r);
    merge(arr,l,m,r);
}