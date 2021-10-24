#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string reshape(int n, string str);
string reshape1(int n, string str);

int main() {
    cout << "shape script"<<endl;
    string str1= "abc de fghij";

    string res = reshape(3,str1);

    // cout <<"input :"<<endl<<str1<<endl <<endl<<"output :"<<endl<< res<<endl;

    res = reshape1(3,str1);

    cout <<endl<<endl<<"input :"<<endl<<str1<<endl <<endl<<"output :"<<endl<< res<<endl;

    return 0;
}

string reshape(int n, string str) {

    str.erase(remove(str.begin(), str.end(), ' '), str.end());
    
    for(int i =0 ;i<str.size() ;i++){
        if( (i+1)%(n+1)==0) str.insert(i, "\n");
    }
    
    return str;
}


string reshape1(int n, string str) {
    
    string res;
    int j=0,tomod=0;

    for(int i =0 ;i<str.size() ;i++){   
        if(str[i]==' ') continue;
        cout<<i <<" "<<str[i];
        if( (tomod!=0) && (tomod%n==0)){
        // cout<<j;
            res.insert(j++,1,'\n');
            res.insert(j++,1,str[i]);
        }else{
            res.insert(j++,1,str[i]);
        }
        tomod++;
    }
cout <<endl;
    for(int i =0 ;i<res.size() ;i++){   
        cout<<res[i];
    }
    return res;
}

// #include <iostream>

// using namespace std;

// int main() {
//     cout << "Hellow World"<<endl;
//     return 0;
// }