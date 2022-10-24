#include <iostream>
#include <sstream>  
#include <string>
#include <vector>
#include <cstring>
#include <bits/stdc++.h>
#include <algorithm>

using namespace std;

int solution(vector<int> &A);

int main(){

    //test cases
    // Example test:   [1, 3, 6, 4, 1, 2]
    // OK

    // Example test:   [1, 2, 3]
    // OK

    // Example test:   [-1, -3]
    // OK

    // vector<int> v{1, 3, 6, 4, 1, 2};
    // sort( v.begin(), v.end() );
    // v.erase( unique( v.begin(), v.end() ), v.end() );
    // //remove values less than 0
    // v.erase( remove_if( v.begin(), v.end(), [](int i){ return i < 0; } ), v.end() );
    // //insert 0 at the beginning
    // v.insert( v.begin(), 0 );
    // for (auto i : v) cout << i << " ";


    // vector<int>::iterator itr = find(v.begin(), v.end(), 0);
	// int index = distance(v.begin(), itr);
    // cout << index << endl;
    
    // for( int i = index; i < v.size(); ++i )
    //     cout << v[i] << " ";

    // cout<<"Hello World"<<endl;

    // int i;
    // for(i=index+1; i < v.size();i++){
    //     if(v[i] != (i-index) ) {
    //         i=i-index;
    //         break;
    //     }
    // }

    // cout<<i<<endl;

    vector<int> v{1, 3, 6, 4, 1, 2};
    cout<<"Res = "<<solution(v)<<endl;
    //5
    vector<int> v1{1, 2, 3};
    cout<<"Res = "<<solution(v1)<<endl;
    //4
    vector<int> v2{-1, -3};
    cout<<"Res = "<<solution(v2)<<endl;
    //1

}

// // write your code in C++14 (g++ 6.2.0)
//     map<int, int> map1;
//     for(size_t i = 0;i < A.size();i++){
//         if(A[i] > 0) map1.insert(pair<int, int>(A[i],i)); 
//         // cout<<A[i]<<endl;
//     }

//     vector<int> positives;
//     map<int, int>::iterator it;

//     if(
//         (map1.size() == 0)
//         || ( *min_element(positives.begin(), positives.end())>1 )
//     ) 
//         return 1;

//     for(it = map1.begin();it != map1.end();it++){
//         positives.push_back(it->first); 
//     }

//     int minelem = *min_element(positives.begin(), positives.end());

//     for(size_t el = minelem;;el++){
//         if(std::find(positives.begin(), positives.end(), el) != positives.end() ) {
//             /* v contains x */
//             continue;
//         } else {
//             return el;
//             /* v does not contain x */
//         }
//     }

int solution(vector<int> &A) {
    // write your code in C++14 (g++ 6.2.0)

    //get unique elements
    sort( A.begin(), A.end() );
    //sort vector 
    A.erase( unique( A.begin(), A.end() ), A.end() );
    //add 0 at the beginning
    A.insert( A.begin(), 0 );
    //get first positive value
    vector<int>::iterator itr = find(A.begin(), A.end(), 0);
    size_t index = distance(A.begin(), itr);
    //get the first missing positive value
    for( size_t i = index+1; i < A.size();i++){
        if(A[i] != (i-index) ) {
            i=i-index;
            return i;
        }
    }
    return A.size();
}
