#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <bits/stdc++.h>

using namespace std;

string solution(int X);

int main(){

    cout << "Hello World" << endl;

    int x = 100;
    cout << solution(x) << endl;

    x = 7263;
    cout << solution(x) << endl;

    x = 3605;
    cout << solution(x) << endl;

    x = 3600;
    cout << solution(x) << endl;

    x = 86461;
    cout << solution(x) << endl;


    return 0;
}

string solution(int X) {
    //X is a number representing the simplified time duration in seconds

    //return the time in the format XwYdZhKmLs
    //where X, Y, Z, K, L are non-negative integers
    //and w, d, h, m, s are the respective abbreviations for weeks, days, hours, minutes and seconds
    if (X < 0){
        return "Invalid input";
    }
    //calculate the number of weeks
    int w = X / (7 * 24 * 60 * 60);
    X = X % (7 * 24 * 60 * 60);

    //calculate the number of days
    int d = X / (24 * 60 * 60);
    X = X % (24 * 60 * 60);

    //calculate the number of hours
    int h = X / (60 * 60);
    X = X % (60 * 60);

    //calculate the number of minutes
    int m = X / 60;
    X = X % 60;

    //calculate the number of seconds
    int s = X;

    //round the number of seconds to the up unit found in the time duration
    if((m>0)&&(s>0)){
        if(h>0){
            m++;
            s=0;
        }else if(d>0){
            m++;
            s=0;
        }else if(w>0){
            m++;
            s=0;
        }


    }
    //round the number of minutes to the up unit found in the time duration
    if((d>0)&&(h>0)&&(m>0)){
        h++;
        m=0;
    }
    //round the number of hours to the up unit found in the time duration
    if((w>0)&&(d>0)&&(h>0)){
        d++;
        h=0;
    }
    

    string result = "";
    if (w > 0){
        result += to_string(w) + "w";
    }
    if (d > 0){
        result += to_string(d) + "d";
    }
    if (h > 0){
        result += to_string(h) + "h";
    }
    if (m > 0){
        result += to_string(m) + "m";
    }
    if (s > 0){
        result += to_string(s) + "s";
    }
    
    return result;
}