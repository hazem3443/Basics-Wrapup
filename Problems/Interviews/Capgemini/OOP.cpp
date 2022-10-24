#include <iostream>
#include <sstream>  
#include <string>
#include <vector>
#include <cstring>

using namespace std;

class shape
{
    protected:
    private:
        /* data */
    public:
        string name;
        int length;
        shape(/* args */string, int);
        ~shape();

        shape* getInst();

        shape* setName(string name);
        string getName();
        int getLength();
        shape* setLength(int length);

        // virtual void prints();
};


class color
{
    private:
        /* data */
    public:
        string colorName;
        color(/* args */string);
        ~color();
        // virtual void prints();
};

class circle: public shape, public color 
{
    private:
        /* data */
    public:
        circle(/* args */string, int);
        ~circle();
        virtual void prints();
};

vector<string> split (string s, string delimiter);

int main(){

    // shape* obj= new shape("circle", 10);
    // cout<<obj->name<<endl;
    // cout<<obj->length<<endl;
    // // cout<<obj->getInst()<<endl;

    // shape* Objhandler = obj->getInst();
    // // cout<<Objhandler->name<<endl;

    // Objhandler->setName("square")->setLength(20);
    // cout<<Objhandler->name<<endl;
    // cout<<Objhandler->length<<endl;

    circle* cobj= new circle("red", 10);
    cout<<cobj->colorName<<endl;
    cout<<cobj->name<<endl;
    cout<<cobj->length<<endl;

    cobj->prints();

    // string str;

    // istream& is = cin;
    // getline(is, str);
  
    string str2 = "aaa bbb ccc ddd eee fff kkk lll";

    vector<string> sres = split(str2, " ");

    for(auto it=sres.begin(); it!= sres.end();it++)
        cout<<*it<<endl;

    cout<<str2<<endl;

    char s2[10];
    for (size_t i = 0; i < 10; i+=2){
        (s2[i]='a'+i);
        (s2[i+1]=' ');

    }

    //strtok char[] and char*
    char *ptr = strtok( s2, " ");
    while (ptr != NULL)  
    {  
        cout << ptr  << endl; // print the string token  
        ptr = strtok (NULL, " , ");  
    }

    //split getline stream
    string s5,T;
    getline(cin, s5);

    stringstream ss(s5);

    while (getline(ss, T, ' ')) {
        cout << T << " - " <<T.size()<< endl;
    }



    //swap func
    int a[5] = { 10, 50, 30, 40, 20 };
    swap(a[0], a[1]);

    for (int i = 0; i < 5; i++)
        cout << a[i] << " ";

    return 0;
}

shape::shape(/* args */string name="", int length=0)
{
    this->name = name;
    this->length = length;
}

shape::~shape()
{
}
shape* shape::getInst(){
    return this;
}
string shape::getName(){
    return this->name;
}
shape* shape::setName(string name){
    this->name = name;
    return this;
}

int shape::getLength(){
    return this->length;
}
shape* shape::setLength(int length){
    this->length = length;
    return this;
}
// void shape::prints(){
//     cout<<"this is shape"<<endl;
// }


color::color(/* args */string colorName="")
{
    this->colorName = colorName;
}

color::~color()
{
}

// void color::prints(){
//     cout<<"this is color"<<endl;
// }


circle::circle(/* args */string colorName="", int length=0):shape("circle", length), color(colorName)
{
}

circle::~circle()
{
}

void circle::prints(){
    cout<<"this is Circle"<<endl;
}


// for string delimiter
vector<string> split (string s, string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

    while ((pos_end = s.find (delimiter, pos_start)) != string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}