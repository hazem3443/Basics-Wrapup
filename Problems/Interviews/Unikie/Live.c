#include <stdio.h> 
#include <string.h>

void possible_Route(char * strArr[], int arrLength) {
  
    // your logic here...
    int i;
    int start;
    //possible routes in circular route .
    int possibleRoutes = (arrLength*(arrLength-1))/2;
    for(i=0; i<possibleRoutes; i++)
    {
        start = 0;
        printf("path number: %i path: %s -> ",i, strArr[start]);
        while(start!=i)
        {
          start++;
          if(start==arrLength)
          start = 0;
          printf("%s -> ", strArr[start]);
        }
        printf("%s", strArr[start]);
}

int main(void) { 
   
  // first element is stations then details g:c and g is amount of gas at that station 
  //c is the gas spent to each that staion
  char * A[] = {"4","3:1","2:2","1:2","0:1"};//gas stations in a circular route
    // char * B[] = {"4","0:1","2:2","5:1"};//gas stations can be in any order
    // char * C[] = {"3","3:2","1:1","1:0"};//gas stations in a % route
  int arrLength = sizeof(A) / sizeof(*A);
  possible_Route(A, arrLength);
  return 0;
    
}

char splitstring(char *input, char *delim) {
    char s;
    scanf ("%d",&s+'/'+);
    // printf("%d",a[0]+a[1]);
       printf("%s", s);
}