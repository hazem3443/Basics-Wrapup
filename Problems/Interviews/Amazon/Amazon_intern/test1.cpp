#include <bits/stdc++.h>
#include <iostream>

using namespace std;

/**
 * the keypad click count is defined as the number of buttons pressed required to print a given string in order to send messages faster.
 * customers tend to set the keypad design in such  a way that the keypad click count is minimized while maintaining its validity
 * givena a string text consisting of lowercase english letters only find the minimum keypad click count required to print the string
 * 
 */

/*
 * Complete the 'minimumKeypadClickCount' function below.
 *
 * The function is expected to return number of clicks to certain keypad design.
 * The function accepts STRING text as parameter.
 */

int minimumKeypadClickCount(string text){
    // 3x3 keypad
    // 1 2 3
    // 4 5 6
    // 7 8 9
    //find map of repeated characters count
    map<char, int> charCount;
    for(int i = 0; i < text.length(); i++){
        charCount[text[i]]++;
    }
      
    //sort the map
    // vector<pair<char, int>> sortedCharCount;
    // for(auto it = charCount.begin(); it != charCount.end(); it++){
    //     sortedCharCount.push_back(make_pair(it->first, it->second));
    // }
    // sort(sortedCharCount.begin(), sortedCharCount.end(), [](pair<char, int> a, pair<char, int> b){
    //     return a.second > b.second;
    // });

    //print the sorted map
    int count = 0;
    int clickCount = 0;
    int index =0;
    for(auto it = charCount.begin(); it != charCount.end(); it++){
        
        if(index%8 == 0)count++;

        clickCount += ((it->second)*count);

        cout <<"idx:"<<index<< "cnt:"<<count<<"clicks:"<<clickCount<<":::"<< it->first << " " << it->second << endl;
        index++;
    }

    
    return clickCount;
}

int main()
{
    // ofstream fout(getenv("OUTPUT_PATH"));

    //example text "abacadefghibj"
    string text = "abacadefghibj";
    int result = minimumKeypadClickCount(text);
    cout << result << "\n";//15

    text = "aaaaaa";
    result = minimumKeypadClickCount(text);
    cout << result << "\n";//6

    text = "abcghdiefjoba";
    result = minimumKeypadClickCount(text);
    cout << result << "\n";//15

    return 0;
}
