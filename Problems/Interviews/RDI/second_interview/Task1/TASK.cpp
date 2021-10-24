#include <iostream>

#include <vector>
#include <fstream>
#include <string>
#include <map>
#include <cstring> 
#include <sstream> 

using namespace std;

using std::cout; using std::cin;
using std::endl; using std::string;
using std::map; using std::copy;

void split_str( std::string const &str, const char delim, std::vector <std::string> &out );

template<typename Map>

void PrintMap(Map& m)
{
    cout << "{ ";
    for (auto &item : m) {
        cout << item.first << ":" << item.second << " ";
    }
    cout << "}\n";
}

int section_flag = 0;

std::vector<std::map<string, string>> maps;

int main()
{
    string line;
    ifstream myfile ("2.rdi");
    
    // map<char, string> map1;
    

    int i=0;

    if (myfile.is_open())
    {
        while ( getline(myfile,line) )
        {
            // line.erase(remove(line.begin(), line.end(), ' '), line.end());
            // cout<<line<<endl;
            
            if (line.empty())
            {
                // cout << "Empty line." << endl;
                section_flag = 0; 
                i++;
            }

            if(line.find("section") != std::string::npos) {
                cout<<"found section"<<endl;
                section_flag = 1;
            }
            
            if(line.find("//") != std::string::npos) ;//cout<<"found comment"<<endl;

            if(line.find("=") != std::string::npos){
            
                if (section_flag == 1)
                    {
                        string key;
                        string value;
                        string temp;
                        cout<<"reading line data"<<endl;
                        // cout<<line<<endl;

                        const char delim = '='; /* define the delimiter like space (' '), comma (,), hyphen (-), etc. */  
                        
                        map<string, string> my_map1;

                        std::vector <std::string> out; // store the string in vector  
                        split_str (line, delim, out); // call function to split the string  
                            
                        my_map1.insert ( pair<string,string>(out[0],out[1]) );

                        maps.push_back(my_map1);
                    }   
                }
        }
        myfile.close();
    }
    else cout << "Unable to open file";


    // cout <<my_map1[0]["BB"]<<endl;
    // my_map1[i].insert( pair<string,string>("out[0]","out[1]") );




    PrintMap(maps[1]);



    // map<int, string> map2;
    // map2[1] = "Banana";
    // map2[2] = "Mango";
    // map2[3] = "Cocoa";
    // map2[4] = "Raspberry";

    // cout << "map2 - ";
    // PrintMap(map2);
    // cout << endl;

    // map<char, string> my_map = {
    // { 'A', "assssdw" },
    // { 'B', "assw" },
    // { 'C', "asdaaaw" }
    // };

    // cout<<my_map['A']<<endl;

    // my_map.insert ( pair<char,string>('Z',"aswww") );

    // cout<<my_map['Z']<<endl;


    // cout<<"test strtok"<<endl;
    // std:: string s2 = "Learn How to split a string in C++";  
    // const char delim = ' '; /* define the delimiter like space (' '), comma (,), hyphen (-), etc. */  
        
    // std::cout << "Your given string is: " << s2;    
    // std::vector <std::string> out; // store the string in vector  
    // split_str (s2, delim, out); // call function to split the string  
        
    // // use range based for loop  
    // for (const auto &s2: out)  
    // {  
    //     std::cout << "\n" << s2;  
    // }

    return 0;
}

void split_str( std::string const &str, const char delim, std::vector <std::string> &out )  
{  
    // create a stream from the string  
    std::stringstream s(str);  
        
    std::string s2;  
    while (std:: getline (s, s2, delim) )  
    {  
        out.push_back(s2); // store the string in s2  
    }  
}  