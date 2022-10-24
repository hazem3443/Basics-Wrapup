#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <bits/stdc++.h>

using namespace std;

int solution(int X, vector<int> &B, int Z);

int main(){

    cout << "Hello World" << endl;

    vector<int> B = {10, 6, 6, 8};
    int z = 2;
    int x = 100;

    cout << solution(x, B, z) << endl;

    return 0;
}

int solution(int X, vector<int> &B, int Z) {
    // write your code in C++14 (g++ 6.2.0)
    //array B have data downloaded at each min from the begining of download
    //Z average of n observations
    //X is the size of the file
    //return the time when the file is downloaded
    int n = B.size();

    //the remaining bytes to download at each min
    //sum of B represents the total bytes downloaded till now
    int sum = 0;
    int remaining=0;
    for (int i = 0; i < n; i++){
        sum += B[i];
        if (sum >= X){
            break;
        }
    }
    if (sum > X){
        return -1;
    }

    remaining = X - sum;


    cout << "remaining: " << remaining << endl;

    //calculate the average of the last Z observations
    int sumZ = 0;
    for (int i = n - Z; i < n; i++){
        sumZ += B[i];
    }
    int avg = sumZ / Z;

    //return the time remaining to download the file
    return remaining / avg;

}