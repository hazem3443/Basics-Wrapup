#include <iostream>
#include <sstream>  
#include <string>
#include <vector>
#include <cstring>
#include <bits/stdc++.h>

using namespace std;

int main(){

    //random values for testing
    vector<int> A = {1,10,5,6,12,5124,4555,2};
    //radix sort
    int max = *max_element(A.begin(), A.end());
    int exp = 1;
    while(max/exp > 0){
        vector<int> b(10);
        for(int i = 0; i < A.size(); i++){
            b[(A[i]/exp)%10]++;
        }
        for(int i = 1; i < 10; i++){
            b[i] += b[i-1];
        }
        vector<int> c(A.size());
        for(int i = A.size()-1; i >= 0; i--){
            c[b[(A[i]/exp)%10]-1] = A[i];
            b[(A[i]/exp)%10]--;
        }
        A = c;
        exp *= 10;
    }
    for(auto i : A){
        cout << i << " ";
    }

    
    cout<<endl;
}

