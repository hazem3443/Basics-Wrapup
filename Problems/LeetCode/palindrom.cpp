#include <iostream>

using namespace std;

class Solution {
public:
    Solution(){

    }
    bool isPalindrome(int x) {
        while(x/10){
            cout<<x<<endl;
            x /= 10;
        }
        return false;
    }
};

int main(){
    Solution s;
    cout<<"Test Case 1  = "<< s.isPalindrome(121) <<endl;
    cout<<"Test Case 2  = "<< s.isPalindrome(-121) <<endl;
    cout<<"Test Case 3  = "<< s.isPalindrome(10) <<endl;
}

