#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream> 
#include <map>

using namespace std;

void split_str( string const &str, const char delim, vector <string> &out );
int compareStrings(string x, string y);
int contains(string x,string y);

int main() {
    
    ifstream MyReadFile("corpus.txt");
   
    
    //parse file into a vector in order of sentences
    string myText;
    vector <string> mainlist ;
    map<string, int> main_map ;

    while (getline (MyReadFile, myText)) {
        vector <string> out; // store the string in vector
        split_str (myText, ' ', out); // call function to split the string     
        for (int i = 0; i < out.size(); i++){
            mainlist.push_back(out[i]);
            //process the list into map of words without repetations
            main_map.insert(pair<string,char>(out[i],0));
        }
    }

    MyReadFile.close();
        
    while(1){
        //order words in the list and keep index of each word in file
        string in;
        map<string, int> match_word ,match_sentence ;

        (cout <<endl<<"Please Type a Text then Press 'ENTER' : " )&& (cin>>in )&& (system("clear") );
        
        //fetch words matched
        for (auto x : main_map)
            if( compareStrings(in,x.first) )
                match_word.insert(pair<string,int>(x.first,0));

        for (auto x : match_word) {
            //search for the sentence start
            for(int i = 0; i < mainlist.size(); i++){
                string sentence;
                if(mainlist[i] == x.first){//if find the word
                    do{
                        int j = i ;
                        sentence.append(mainlist[i]).append(" ");
                    }while( (!(contains(mainlist[i++],"\"?:;{<('-,.\n")) ));
                    
                    sentence.resize(sentence.size() - 1);

                    if( (x.first.compare(sentence)) != 0)
                        match_sentence.insert(pair<string,int>(sentence,0));
                }
            }
        }

        cout << "Words:" ;
        for (auto x : match_word)
            cout << "\t\t"<<x.first << endl;

        cout << endl <<"quote:" ;
        for (auto x : match_sentence)
            cout << "\t\t" << x.first <<endl;
    }
   return 0;
}

void split_str( string const &str, const char delim, vector <string> &out )  
{  
    // create a stream from the string  
    stringstream s(str);  
        
    string s2;  
    while (getline (s, s2, delim) )  
    {  
        out.push_back(s2); // store the string in s2  
    }  
}
int compareStrings(string x, string y){
    int i=0;

    while (x[i] == y[i])i++;
    if(x.size() == i ){
        return 1;
    }
    else return 0;
}

int contains(string x,string y){
    //checks string 1 is inside string 2
    int res=0;    
    for(int i=0;i < y.size();i++){
        res += (x.find(y[i]) != string::npos);
    }
    return res;
}