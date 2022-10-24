#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#define PAUSE myPause()

#define KEYWORD 2
#define WORDS 250
#define MAX_LETTER 30

// FUNCTION PROTOTYPES

void compAndCount(char loadKey[][MAX_LETTER], char resume[][MAX_LETTER]);

void myPause();

void readAndLoadKeyword(char loadKey[][MAX_LETTER]);

// MAIN FUNCTION

int main()
{

    char loadKey[KEYWORD][MAX_LETTER];
    char resume[WORDS][MAX_LETTER];

    // load keywords from keywords file into array loadKey[]

    readAndLoadKeyword(loadKey);

    for (int j = 0; j < KEYWORD; j++)

    {

        puts(loadKey[j]);
    }

    puts("\n");

    // compare and count the occurrences of keyword in resumes file

    compAndCount(loadKey, resume);
}

// FUNTIONS

void compAndCount(char loadKey[][MAX_LETTER], char resume[][MAX_LETTER])
{

    FILE *fpr;

    fpr = fopen("resumes.txt", "r");

    int r = 0, count = 0, num = 0, res = 0;

    char temp;

    while ((temp = fgetc(fpr)) != EOF)
    {

        if (temp != ' ' && temp != '\n')
        {

            resume[res][r] = temp;

            r++;
        }

        else

        {

            resume[res][r] = '\0';

            r = 0;

            res++;
        }
    }

    printf("words in resume file %i\n", res);

    for (int j = 0; j <= res; j++)

    {

        puts(resume[j]);
    }

    puts("\n");

    

    // way 1 to compare and count (WRONG?)

    // for (int i = 0; i < res; i++) {

    //     if (i < KEYWORD) {

    //     scanf(" %[^\n]", loadKey[i]);

    //     }

    //     scanf(" %[^\n]", resume[i]);

    // }

    for (int k = 0; k < KEYWORD; k++) { // loop through keywords
        for (int l = 0; l <= res; l++) {// loop through resumes words
            if (strcmp(loadKey[k], resume[l]) == 0) {//compare keywords and resumes words
                count++;//count the number of occurrences of keywords in resumes
            }
        }
    }

    /*

    // way 2 to compare and count (WRONG?)

    char key[MAX_LETTER] = {'\0'}, r[MAX_LETTER] = {'\0'};

    for (int i = 0; i < KEYWORD; i++) {

    strcpy(key, loadKey[i]);

    for (int l = 0; l < res; l++) {

    strcpy(r, resume[l]);

    if (strcmp(key, r) == 0)

    count++;

    }

    }

    */

    printf("Resume Rating: %i\n", count);

    fclose(fpr);

} // end compAndCount

void myPause()
{

    puts("\nPress ENTER to continue\n");

    exit(0);
}

void readAndLoadKeyword(char loadKey[][MAX_LETTER])
{

    FILE *fp;

    fp = fopen("keywords.txt", "r");

    char ch;

    int row = 0, col = 0;

    if (fp == NULL)
    {

        puts("Not able to open keyword file!");

        PAUSE;
    }

    // load 25 keywords and ',' into an array line[]

    char line[181]; // 180 characters + '\0'

    fgets(line, 181, fp);

    puts(line);

    puts("\n");

    // load 25 words in array line[] into array loadKey[]

    for (int i = 0; i < 180; i++)
    {

        ch = line[i];

        if (ch != ',')
        {

            loadKey[row][col] = ch;

            col++;
        }

        else
        {

            loadKey[row][col] = '\0';

            col = 0;

            row++;
        }
    }

    fclose(fp);

} // end readAndLoadKeyword