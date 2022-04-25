void main(){
    //write to memory a certain value and read it back 
    int x = 0x01234567; //suppose int has a 4 byte size 

    char b1 = (char) x;// 1 byte

    if(b1 == 0x01)     printf("big endinet");
    else     printf("little endiant");

}



/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>

void print_diag();

int main()
{
    print_diag();
    return 0;
}

void print_diag(){
    char xs[10]; 
    for(int i=0;i<10;i++){
        
        printf("%sx\n",xs);
        xs[i] = " "

    }
}