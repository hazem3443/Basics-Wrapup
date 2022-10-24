#include <iostream>
#include <sstream>  
#include <string>
#include <vector>
#include <cstring>
#include <bits/stdc++.h>

using namespace std;

int main(){
    int n;
    cin >> n;
    int a[n];
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    //calculate time of the algorithm
    //Radix sort
    clock_t t;
    t = clock();
    //radix sort
    int max = *max_element(a, a+n);
    int exp = 1;
    while(max/exp > 0){
        vector<int> b(10);
        for(int i = 0; i < n; i++){
            b[(a[i]/exp)%10]++;
        }
        for(int i = 1; i < 10; i++){
            b[i] += b[i-1];
        }
        vector<int> c(n);
        for(int i = n-1; i >= 0; i--){
            c[b[(a[i]/exp)%10]-1] = a[i];
            b[(a[i]/exp)%10]--;
        }
        for(int i = 0; i < n; i++){
            a[i] = c[i];
        }
        exp *= 10;
    }

    //print
    for(int i = 0; i < n; i++){
        cout << a[i] << " ";
    }
    //end calculating time
    t = clock() - t;
    cout << endl << "Time: " << ((float)t)/CLOCKS_PER_SEC << endl;

    //Counting Sort
    t = clock();
    //counting sort
    int max2 = *max_element(a, a+n);
    int min2 = *min_element(a, a+n);
    int range = max2 - min2 + 1;
    vector<int> count(range), output(n);
    for(int i = 0; i < n; i++){
        count[a[i]-min2]++;
    }
    for(int i = 1; i < count.size(); i++){
        count[i] += count[i-1];
    }
    for(int i = n-1; i >= 0; i--){
        output[count[a[i]-min2]-1] = a[i];
        count[a[i]-min2]--;
    }
    for(int i = 0; i < n; i++){
        a[i] = output[i];
    }
    //print
    for(int i = 0; i < n; i++){
        cout << a[i] << " ";
    }
    //end calculating time
    t = clock() - t;
    cout << endl << "Time: " << ((float)t)/CLOCKS_PER_SEC << endl;
    



    return 0;
}