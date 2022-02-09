#include <iostream>
#include <list>
#include <vector>
#include <algorithm>

using namespace std;

void findZigZagSequence(vector<int> a, int n);

int main()
{
    vector<int> vect{ 1, 2, 3, 4, 5, 6, 7 };

    findZigZagSequence(vect,vect.size());

    return 1;
}

void findZigZagSequence(vector < int > a, int n){
    sort(a.begin(), a.end());
    int mid = ((n + 1)/2)-1;
    swap(a[mid], a[n-1]);

    int st = mid + 1;
    int ed = n - 2;
    while(st <= ed){
        swap(a[st], a[ed]);
        st = st + 1;
        ed = ed - 1;
    }
    for(int i = 0; i < n; i++){
        if(i > 0) cout << " ";
        cout << a[i];
    }
    cout << endl;
}