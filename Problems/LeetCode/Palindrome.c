#include <stdio.h>
#include <stdlib.h>

// bool isPalindrome(int x);
int like_log(int x);
void swapByReference(int *x, int *y);

int *divide(int *arr, int len);
int *merge(int *l1, int l1_len, int *l2, int l2_len, int *arr);
void counting_sort(int *arr, int len, int range);

void main()
{
    // printf("asd %i\n", like_log(10));

    // const int x = 10;

    // printf("%i\n", x);
    // int *px = &x;

    // *px = 11;
    // printf("%i\n", x);

    int arr[] = {1, 10, 8, 3, 4, 9, 23, 2, 6, 3}; // 10 size
    int len = 10;

    {
        // // bubble
        // //  asc
        // for (int i = 0; i < len - 1; i++)
        //     for (int j = 0; j < len - i - 1; j++)
        //         if (arr[j] > arr[j + 1])
        //         {
        //             // swap
        //             arr[j] += arr[j + 1];             // x = x+y
        //             arr[j + 1] = arr[j] - arr[j + 1]; // y = x+y - y = x
        //             arr[j] = arr[j] - arr[j + 1];     // x = x+y-x = y
        //         }

        // for (int i = 0; i < len; i++)
        //     printf("%i\n", arr[i]);

        // // int x = 10, y = 11;
        // // // swap
        // // x += y;    // x = x+y
        // // y = x - y; // y = x+y
        // // x -= y;
        // // printf("swap x = %i, y = %i", );
    }

    {
        // insertion sort
        // int sel;
        // for (int i = 1, sel = arr[i]; i < len; i++, sel = arr[i])
        //     for (int j = i; j > 0 && sel < arr[j - 1]; j--)
        //     {
        //         if (arr[j - 1] > arr[j])
        //         {
        //             // printf("val = %i\n", sel);
        //             // swap
        //             swapByReference(arr + j, arr + (j - 1));
        //         }
        //     }

        // for (int i = 0; i < len; i++)
        //     printf("%i\n", arr[i]);
    }

    {
        // merge
        // divide(arr, len);
        // for (int i = 0; i < len; i++)
        //     printf("%i\n", arr[i]);

    }

    {
        // counting
        // counting_sort(arr, len, 23);

        // for (int i = 0; i < len; i++)
        //     printf("%i\n", arr[i]);
    }

    {
        // palindrome
        char number_str[10];
        int number = 12323;

        sprintf(number_str, "%d", number);
        int i = 0, j = 4; // len = 3 , j =len-1;

        while (number_str[i] == number_str[j] && i != j)
            i++, j--;

        if (i == j)
            printf("palindrom");
        else
            printf("not palindrom");
    }
}

void counting_sort(int *arr, int len, int range)
{
    int counting[range + 1];
    for (int i = 0; i < range; i++)
        counting[i] = 0;

    for (int i = 0; i < len; i++)
        counting[arr[i]]++;

    for (int i = 0, cur = 0; i <= range; i++)
        while (counting[i] != 0)
        {
            arr[cur++] = i;
            counting[i]--;
        }

    // printf("counts");
    // for (int i = 0; i < range; i++)
    //     printf("%i\n", counting[i]);
}
int *divide(int *arr, int len)
{

    if (len == 1)
        return arr;

    int mid = len / 2;

    int *l1 = divide(arr, mid);
    int *l2 = divide(arr + mid, len - mid);

    return merge(l1, mid, l2, len - mid, arr);
}

int *merge(int *l1, int l1_len, int *l2, int l2_len, int *arr)
{
    printf("into merge ");
    for (int i = 0; i < l1_len + l2_len; i++)
        printf("%i, ", arr[i]);
    printf("\n");

    int i = 0, j = 0, cur = 0;
    int *l3 = (int *)malloc((l1_len + l2_len) * sizeof(int));
    while (i < l1_len && j < l2_len)
    {
        if (l1[i] <= l2[j])
            l3[cur++] = l1[i++];
        else
            l3[cur++] = l2[j++];
    }
    while (i < l1_len)
        l3[cur++] = l1[i++];
    while (j < l2_len)
        l3[cur++] = l2[j++];

    for (int i = 0; i < (l1_len + l2_len); i++)
        arr[i] = l3[i];

    return arr;
}

// bool isPalindrome(int x)
// {
//     // while (like_log(x));
// }

int like_log(int x)
{
    if (x == 1)
        return 0;

    int k = like_log(x / 10);

    return ++k;
}

void swapByReference(int *x, int *y)
{                 // O(3) -- S(0)
    *x = *y + *x; // x= x+y
    *y = *x - *y; // y = x+y-y = x
    *x = *x - *y; // x = x+y-x = y
}