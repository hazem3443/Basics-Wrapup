#include <bits/stdc++.h>

using namespace std;

void miniMaxSum(vector<int> arr);
string timeConversion(string s);

int main()
{
    vector<int> arr(5);

    // string str = "12:45:54PM";

    // int s = str.at(1) - '0';

    // cout <<timeConversion(str)<<endl;
    return 0;
}

string timeConversion(string s) {
    int pos = s.find(":");
    int t = stoi(s.substr(0,pos));
    string r = s.substr(8,2);
    if(t == 12 && r =="AM")return "00"+s.substr(pos,6);
    else if(t <12 && r=="PM")return to_string((t+12))+s.substr(pos,6);
    else return s.substr(0,8);
}

void miniMaxSum(vector<int> arr)
{
    int max=0, maxi=4, maxres=0, min=0, mini=0, minres=0;
    max = arr[4];
    min = arr[0];
    for (int i = 0; i < arr.size(); i++)
    {
        if (max < arr[i]){
            max = arr[i];
            maxi = i;
            // cout<<"i";
        }
        else if (min > arr[i]){
            min = arr[i];
            mini = i;
            // cout<<"i";
        }
    }
    
    maxres = max;
    minres = min;
    arr[mini] = 0;
    arr[maxi] = 0;

    for (int i = 0; i < arr.size(); i++)
    {
        // cout << "res "<<minres<<" "<<maxres<<endl;
        minres += arr[i];
        maxres += arr[i];
    }

    cout << minres << " " <<maxres <<endl;
}
