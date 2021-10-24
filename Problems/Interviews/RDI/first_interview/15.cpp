#include <iostream>

using namespace std;

int getBit(unsigned int val, int pos);

int main() {
    cout << "Hellow World"<<endl;

    cout << "BitPos(5,0) = "<<getBit(5,0)<<endl;
    cout << "BitPos(5,1) = "<<getBit(5,1)<<endl;
    cout << "BitPos(5,2) = "<<getBit(5,2)<<endl;
    return 0;
}

int getBit(unsigned int val, int pos){
    return ((val & (1<<pos) )>>pos);
}