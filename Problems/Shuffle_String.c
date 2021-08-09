//start at 9.56 ends at 10.17
//submitted at 10.25
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *restoreString(char *s, int *indices, int indicesSize);
void print_arr(int *nums, int numsSize);

void main()
{
    char *s = "codeleet";
    int indices[] = {4, 5, 6, 7, 0, 2, 1, 3};

    char *res = restoreString(s, indices, 8);
    //test case 1
    char *testcase1 = (strcmp(res, "leetcode") == 0 ? "Passed" : "Failed");
    printf("Test Case 1 %s \t in = %s\t out = %s\n", testcase1, s, res);
}

char *restoreString(char *s, int *indices, int indicesSize)
{
    char *new_s = malloc((indicesSize + 1) * sizeof(char));
    for (int i = 0; i < indicesSize; i++)
        new_s[indices[i]] = s[i];

    return new_s;
}

void print_arr(int *nums, int numsSize)
{
    printf("[");
    for (int i = 0; i < numsSize; i++)
        printf(" %i,", nums[i]);
    printf("\b ]");
}