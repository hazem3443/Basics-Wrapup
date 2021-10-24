#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unistd.h>
#include <fstream>
#include <sstream> 
#include <regex>

using namespace std;

void split_str( string const &str, const char delim, vector <string> &out );
int compareStrings(string x, string y);

int main() {
    
    ifstream MyReadFile("corpus.txt");
   
    string myText;
   
    size_t ix =0;
    
    vector <string> mainlist ;
    while (getline (MyReadFile, myText)) {
        //iterate each line
        vector <string> out; // store the string in vector  
        //we can build a tree with chars relations and then add those trees by reference to a dictionary

        split_str (myText, ' ', out); // call function to split the string     
        for (int i = 0; i < out.size(); i++){
            // cout<< out[i]<<endl;
            mainlist.push_back(out[i]);
        }
        ix+=out.size();
    }
    // cout <<ix;
    // Close the file
    MyReadFile.close();
    
    //process the list
    map<string, int> main_map ;

    for (int i = 0; i < mainlist.size(); i++){
        // map<string, int>::iterator it;
        // it = my_map.find(mainlist[i]);
        // it[]
        main_map.insert(pair<string,char>(mainlist[i],0));
        // cout<< mainlist[i]<<endl;
    }
    // cout <<endl<<main_map.size()<<endl;
    string in;

    //order words in the list and keep index of each word in file

    int resa = compareStrings("nev", "never");
    // cout << resa << endl;
    resa = compareStrings("nev", "saever");
    // cout << resa << endl;
    resa = compareStrings("nev", "aswnever");
    // cout << resa << endl;

    map<string, int> match ;
    do{
        cout <<"Please Type a Text then Press 'ENTER' :"<<endl;
        cin>>in;
        system("clear");
        for (int i = 0; i < mainlist.size(); i++){
            if( compareStrings(in,mainlist[i])) 
                match.insert(pair<string,char>(mainlist[i],0));
        }

        for (auto x : match) {
            cout << x.first << "\n";
        }
        // cout <<match.size() << endl;
    }
    while(1);
    return 0;
}

void split_str( string const &str, const char delim, vector <string> &out )  
{  
    // create a stream from the string  
    std::stringstream s(str);  
        
    std::string s2;  
    while (std:: getline (s, s2, delim) )  
    {  
        out.push_back(s2); // store the string in s2  
    }  
}
int compareStrings(string x, string y){
    int i=0;
    while (x[i] == y[i])i++;

    if(x.size() == i || y.size() == i){
        return 1;
    }
    else return 0;
}