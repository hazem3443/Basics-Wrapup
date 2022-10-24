// you can use includes, for example:
// #include <algorithm>
#include <iostream>
#include <sstream>  
#include <string>
#include <vector>
#include <cstring>
#include <bits/stdc++.h>
#include <algorithm>
// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;

using namespace std;

int solution(vector<int> &A) {
    //counting sort the array
    //radix sort
    int max = *max_element(A.begin(), A.end());
    int min = *min_element(A.begin(), A.end());
    int range = max - min + 1;
    int count[range];
    memset(count, 0, sizeof(count));
    for(int i = 0; i < A.size(); i++){
        count[A[i] - min]++;
    }
    int j = 0;
    for(int i = 0; i < range; i++){
        while(count[i] > 0){
            A[j++] = i + min;
            count[i]--;
        }
    }
    //find the missing number
    int missing = 1;
    for(int i = 0; i < A.size(); i++){
        if(A[i] == missing){
            missing++;
        }
    }
    return missing;
}

int main(){

    vector<int> arr = {1, 3, 6, 4, 1, 2};
    cout<<"res = "<<solution(arr)<<endl;


    vector<int> arr1 = {1, 2, 3};
    cout<<"res = "<<solution(arr1)<<endl;

    vector<int> arr2 = {-1, -3};
    cout<<"res = "<<solution(arr2)<<endl;

    return 0;
}

//test cases
// Example test:   [1, 3, 6, 4, 1, 2]
// OK

// Example test:   [1, 2, 3]
// OK

// Example test:   [-1, -3]
// OK