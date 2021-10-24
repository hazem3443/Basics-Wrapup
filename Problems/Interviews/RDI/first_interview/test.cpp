#include <iostream>
#include <cstdlib>
#include <string> 
#include <cmath>
#include <fstream>
#include <map>

using namespace std;

void display(int n[], int length) ;

int main(void){
    cout << "Hellow World"<<endl;
    int x[] ={1,2,3,4,5};
    display(x,sizeof(x)/sizeof(int));


    string str = (string)"hi " + to_string(12) ;
    cout << str << endl;
    cout << str.size() << endl;
    cout << str.length() << endl;

    string firstName;
    cout << "Type your first name: ";
    cin >> firstName; // get user input from the keyboard
    cout << "Your name is: " << firstName<<endl;

    cout << max(1, 12) <<endl;
    cout << min(1, 12) <<endl;
    cout << sqrt(64) <<endl;
    cout << round(2.6) <<endl;
    cout << log(2) <<endl;


    // Create and open a text file
    ofstream MyFile("filename.txt");
    ofstream MyFile1("filename1.txt");
    // Write to the file
    MyFile << "Files can be tricky, but it is fun enough!";
    MyFile1 << ",:D Files 1 can be tricky, but it is fun enough! :D";
    // Close the file

    MyFile.close();
    MyFile1.close();

    //read files
    ifstream MyReadFile("filename.txt");
    ifstream MyReadFile1("filename1.txt");

    string myText;
    string myText1;

    // Use a while loop together with the getline() function to read the file line by line
    while (getline (MyReadFile, myText) || getline (MyReadFile1, myText1)) {
    // Output the text from the file
        cout << myText << endl<< myText1<<endl;
    }

    // Close the file
    MyReadFile.close();
    MyReadFile1.close();

    //dictionart
    map<char, char> my_map = {
        { 'A', '1' },
        { 'B', '2' },
        { 'C', '3' }
    };

    my_map.insert(pair<char,char>('Z','9'));
    
    map<char,char>::iterator it;
    it = my_map.find('Z');
    // my_map.erase(it,my_map.end());
    
    map< int,map<string,double> > map_data;

    map<string, double> data;

    data.emplace("window", 3.14);

    map_data.emplace(0, data);

    cout<<"Reading map :"<<( typeid(map_data[0]).name() ==  typeid(map<string,double>).name() )<<endl;//["window"]<<endl;


    return 0;    

}

void display(int n[],int length) {
    cout << "Displaying Values: " << endl;
    for (int i = 0; i < length ; ++i) {
        cout << "num[" << i << "]: " << n[i] << endl;
    }
}