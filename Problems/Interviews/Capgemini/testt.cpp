#include <iostream>

using namespace std;

//generic macro to read any DIO pin using shifting with register address
#define READ_PIN(REG, PIN_NUMBER) ((REG >> PIN_NUMBER) & 0x01)

int main(){
    // cout << "Hello World!";
    typedef int arr[5];
    arr iarr={1,2,3,4,5};
    int i;
    for (i=0; i < 4; i++)
    {
        printf("%d", iarr[i]);
        /* code */
    }
    

    return 0;
}