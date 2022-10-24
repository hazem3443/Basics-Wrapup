#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

// #define predigit(num1, num2) \
//     romanval[i++] = num1;\
//     romanval[i++] = num2;\

// #define postdigit( c, n) \
//     for (int j = 0; j < n; j++)\
//         romanval[i++] = c;\


int findIndex(char* rom_lets, char c) {
    for (int i = 0; i < 7; i++){
        if(rom_lets[i] == c) return i;
    }
    return -1;
}

void findRoman(int number);

void find_romanValue(char *res_container,int number);

// char rom_lets[] ={'I','V','X','L','C','D','M'};
// int  rom_vals[] ={1  ,5  , 10, 50,100,500,1000};

void main(){
    // //create roman numerals arr

    // int val = 50;//L
    // findRoman(val);
    // val = 1100;//MC
    // findRoman(val);

    // val = 950;//CML - 
    // findRoman(val);

    char* res[10]={0};
    find_romanValue((char*)res, 1100);// M
    // print result
    printf("%s", (char*)res);

}


// void findRoman(int number){
//     char romanval[1000]={0};

//     int j;
//     if (number <= 0)
//     {
//         printf("Invalid number");
//         return;
//     }
//     while (number != 0)
//     {
//         if (number >= 1000)
//         {
//             postdigit('M', number / 1000);
//             number = number - (number / 1000) * 1000;
//         }
//         else if (number >= 500)
//         {
//             if (number < (500 + 4 * 100))
//             {
//                 postdigit('D', number / 500);
//                 number = number - (number / 500) * 500;
//             }
//             else
//             {
//                 predigit('C','M');
//                 number = number - (1000-100);
//             }
//         }
//         else if (number >= 100)
//         {
//             if (number < (100 + 3 * 100)) 
//             {
//                 postdigit('C', number / 100);
//                 number = number - (number / 100) * 100;
//             }
//             else
//             {
//                 predigit('L', 'D');
//                 number = number - (500 - 100);
//             }
//         }
//         else if (number >= 50 )
//         {
//             if (number < (50 + 4 * 10))
//             {
//                 postdigit('L', number / 50);
//                 number = number - (number / 50) * 50;
//             }
//             else
//             {
//                 predigit('X','C');
//                 number = number - (100-10);
//             }
//         }
//         else if (number >= 10)
//         {
//             if (number < (10 + 3 * 10))
//             {
//                 postdigit('X', number / 10);
//                 number = number - (number / 10) * 10;
//             }
//             else
//             {
//                 predigit('X','L');
//                 number = number - (50 - 10);
//             }
//         }
//         else if (number >= 5)
//         {
//             if (number < (5 + 4 * 1))
//             {
//                 postdigit('V', number / 5);
//                 number = number - (number / 5) * 5;
//             }
//             else
//             {
//                 predigit('I', 'X');
//                 number = number - (10 - 1);
//             }
//         }
//         else if (number >= 1)
//         {
//             if (number < 4)
//             {
//                 postdigit('I', number / 1);
//                 number = number - (number / 1) * 1;
//             }
//             else
//             {
//                 predigit('I', 'V');
//                 number = number - (5 - 1);
//             }
//         }
//     }
//     printf("Roman number is: ");
//     for(j = 0; j < i; j++)
//         printf("%c", romanval[j]);
//     printf("\n");
// }
void find_romanValue(char *res_container,int number){
    //index{'I','V','X','L','C','D','M'};
    int index_arr[7]={0};
    //starting with M
    int selected_num_index = 6;//M

    int number_rem = number;

    char rom_lets[] ={'I','V','X','L','C','D','M'};
    int  rom_vals[] ={1  ,5  , 10, 50,100,500,1000};
    int  rom_res[7] ={0};
    //(sizeof(rom_lets)/sizeof(char))-1
    while(number_rem!=0){
        for(int i=6;i>=0;i--){
            //start from last character of the number
            unsigned int index_no = findIndex(rom_lets, rom_lets[i]);
            if(index_no>=0){
                //valid index available for this number
                int sel_let_val = rom_vals[index_no];

                rom_res[index_no] = (number_rem/sel_let_val);
                //then move to the next value.
                number_rem = number_rem - (number_rem/sel_let_val)*sel_let_val;

                // number_rem = 0;//number_rem - ((number_rem/1000)*1000);
            }
        }
    }
    //fill in the res_container with roman values
    int res_i=0;
    for(int j=6;j>=0;j--)
    {
        if(rom_res[j])
            res_container[res_i++]=rom_lets[j];
    }
}