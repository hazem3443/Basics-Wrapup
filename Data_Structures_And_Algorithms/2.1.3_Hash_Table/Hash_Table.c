#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 20

typedef struct DataItem
{
    int data;
    int key;
} DateItem_Type;

DateItem_Type *hashArray1[SIZE]; //array of pointers of type DateItem

void display(DateItem_Type *hashArr[]);
DateItem_Type *delete (DateItem_Type *hashArr[], struct DataItem *item);
void insert(DateItem_Type *hashArr[], int key, int data);
struct DataItem *search(DateItem_Type *hashArr[], int key);
int hashCode(int key);

int main()
{
    insert(hashArray1, 1, 20);
    insert(hashArray1, 2, 70);
    insert(hashArray1, 42, 80);
    insert(hashArray1, 4, 25);
    insert(hashArray1, 12, 44);
    insert(hashArray1, 14, 32);
    insert(hashArray1, 17, 11);
    insert(hashArray1, 13, 78);
    insert(hashArray1, 37, 97);

    display(hashArray1);
    DateItem_Type *item = search(hashArray1, 37);

    if (item != NULL)
    {
        printf("Element found: %d\n", item->data);
    }
    else
    {
        printf("Element not found\n");
    }

    delete (hashArray1, item);
    item = search(hashArray1, 37);

    if (item != NULL)
    {
        printf("Element found: %d\n", item->data);
    }
    else
    {
        printf("Element not found\n");
    }
    display(hashArray1);
}

int hashCode(int key)
{ //hash function
    return key % SIZE;
}

struct DataItem *search(DateItem_Type *hashArr[], int key)
{
    //get the hash
    int hashIndex = hashCode(key);
    //move in array until an empty
    while (hashArr[hashIndex] != NULL)
    {
        if (hashArr[hashIndex]->key == key)
            return hashArr[hashIndex]; //return pointer of type DateItem_Type
        //go to next cell
        ++hashIndex;
        //wrap around the table
        hashIndex %= SIZE;
    }
    return NULL; //return null pointer
}

void insert(DateItem_Type *hashArr[], int key, int data)
{
    struct DataItem *item = (struct DataItem *)malloc(sizeof(struct DataItem));
    item->data = data;
    item->key = key;

    //get the hash
    int hashIndex = hashCode(key);

    //following linear probing technique
    //move in array until an empty or deleted cell
    while (hashArr[hashIndex] != NULL && hashArr[hashIndex]->key != -1)
    {
        //go to next cell
        ++hashIndex;

        //wrap around the table
        hashIndex %= SIZE;
    }
    hashArr[hashIndex] = item;
}

DateItem_Type *delete (DateItem_Type *hashArr[], struct DataItem *item)
{
    int key = item->key;

    //get the hash
    int hashIndex = hashCode(key);
    //move in array until an empty
    while (hashArr[hashIndex] != NULL)
    {
        if (hashArr[hashIndex]->key == key)
        {
            DateItem_Type *temp;
            temp = hashArr[hashIndex];
            //assign a dummy item at deleted position
            hashArr[hashIndex]->key = -1;
            hashArr[hashIndex]->data = -1;

            return temp;
        }
        //go to next cell
        ++hashIndex;
        //wrap around the table
        hashIndex %= SIZE;
    }
    return NULL;
}

void display(DateItem_Type *hashArr[])
{
    int i = 0;
    for (i = 0; i < SIZE; i++)
    {
        if (hashArr[i] != NULL)
            printf(" (%d,%d)", hashArr[i]->key, hashArr[i]->data);
        else
            printf(" ~~ ");
    }
    printf("\n");
}