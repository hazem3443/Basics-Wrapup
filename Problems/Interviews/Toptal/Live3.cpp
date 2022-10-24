#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <bits/stdc++.h>

using namespace std;

vector<string> solution(string &S, vector<string> &B);

int main(){

    cout << "Hello World" << endl;

    string s = "300.01";
    vector<string> b = {"300.00", "200.00", "100.00"};
    vector<string> result = solution(s, b);
    for (int i = 0; i < result.size(); i++){
        cout << result[i] << endl;
    }

    return 0;
}

vector<string> solution(string &S, vector<string> &B){
    //sum of B
    int sum = 0;
    //string S to float
    float s_float = stof(S);
    cout << s_float << endl;
    for (int i = 0; i < B.size(); i++){
        sum += stoi(B[i]);
    }
    //convert B ton array of integers
    int *B_int = new int[B.size()];
    for (int i = 0; i < B.size(); i++){
        B_int[i] = stoi(B[i]);
    }
    //sort B_int in descending order
    sort(B_int, B_int + B.size(), greater<int>());

    //print B_int
    vector<string> result;
    float prev_res= 0;
    float prev_inc = s_float;
    for (int i = 0; i < B.size(); i++){
        //calculate sum before current element
        int sum_before = 0;
        for (int j = 0; j < i; j++){
            sum_before += B_int[j];
        }
        int cur_sum = sum - sum_before;
        cout << "cur_sum: " << cur_sum << endl;
        // cout << B_int[i] << endl;
        prev_res = (prev_inc * B_int[i])/cur_sum;
        cout << "prev_res: " << prev_res << endl;
        prev_inc -= prev_res;
        result.push_back(to_string( prev_res ) );
        // prev_res = s_float - prev_inc;

    }
    return result;
}