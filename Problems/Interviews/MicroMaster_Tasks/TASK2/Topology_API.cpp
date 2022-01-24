#include <iostream>
#include <list>
#include <vector>

using namespace std;

class A
{
    public:
    int x;
    int y;
    virtual void ham(int x, int y) {
        this->x = x;
        this->y = y;
        cout << "mother" << endl; 
    }
};

class B : public A
{
    public:
    int z;
    void ham(int x) { 
        this->x = x;
        cout << "daughter" << endl; }
};

class C : public A
{
    public:
    int l;
    void hams(int x) { 
        this->x = x;
        cout << "daughter" << endl; }
};

class general_type:public B,public C{};

general_type func(int asd){
    general_type res;
    res.B::z = asd;
    return res;
}

int main()
{

    general_type g;
    g.B::z = 20;
    g.C::l = 10;
    general_type r1= func(100);
    // cout << r1.B::z << endl;
    // cout << g.B::z<<endl<< g.C::l << endl;

    vector<general_type> tops;
    tops.push_back(g);

    cout<<(tops[0]).B::z<<endl;

}