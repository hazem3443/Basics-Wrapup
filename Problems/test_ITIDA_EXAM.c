#include <stdio.h>
#include <stdlib.h>
// #define SQ(x) x*x


char s1(int x,int y);

char (*p(int,int))[10];


void main(){
    // float s=10,u =30,t=2,a;

    // for(int i=0;i<10;i++)

    //    *p = s1;

    int a[3][4] = {1,2,3,4,5,6,7,8,9,10,11,12};
    printf("%i\n",sizeof(int));

    printf("%u, %u, %u",a,a+1,&a+1);

    // for(int i=0;i<10;i++)
    //    * (p+i)(1,2);
    // a = 2*(s-u*2)/SQ(t);
    // printf("Hello World! %f\n",a);
}

char s1(int x,int y){
    printf("x = %d, y = %d\n",x,y);
    
    // return (char*)malloc(10);
    return 'a';
}
