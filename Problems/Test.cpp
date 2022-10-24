#include <iostream>

using namespace std;

class human{
    protected:
        string name;
        string country;
        int age;

        human(string name, string country, int age){
            human::name = name;
            human::country = country;
            human::age = age;
            cout << "human constructed protected"<<endl;
        }
    public:
        human(){
            cout << "human Constructed"<<endl;
        }
        ~human(){
            cout << "human Destructed"<<endl;
            // cout << "human "<<human::name << " destroyed" << endl;
        }
        void setname(string n){name = n;}
        string getname(){return name;}
        void setcountry(string c){country = c;}
        string getcountry(){return country;}
        void setage(int a){age=a;}
        int getage(){return age;}
};
class men:public human{
    private:
        int strength;
    public:
        men(int x=10){
            cout << "Men Constructed "<<x<<endl;
        }
        int getage(){
            cout<<"\nthis is age"<<endl;
            return men::age;
        }
        int getage(int x){
            cout<<"\nthis is age "<<x<<endl;
            return men::age;
        }
        int getage(string k){
            cout<<"\nthis is age string "<<k<<endl;
            return men::age;
        }
        ~men(){
            cout << "Men destructed"<<endl;
        }
        void setstrength(int s){men::strength = s;}
        int getstrength(){return men::strength;}
};

int main(){
    human* x = new human();
    x->setname("x");
    x->setcountry("Egypt");
    x->setage(10);

    cout << "name : " << x->getname() << " ,country : " << x->getcountry() << " ,Age : " << x->getage() <<endl;

    delete x;

    men* der_x = new men();

    der_x->setname("man white");
    der_x->setage(50);
    der_x->setstrength(11);
    
    cout << "name : " << der_x->getname() << " ,country : " << der_x->getcountry() << " ,Age : " << der_x->getage("sw") << " ,strength : " << der_x->getstrength() <<endl;

    cout << "Point"<<endl;

    // Square x = Square();
    // cout <<"is instance of "<<(instanceof<Square>(&x) )<<endl;
    // cout <<"is instance of "<<(is_base_of<Square,typeof(x)>::value)<<endl;

/*
template<typename Base, typename T>
inline bool instanceof(const T*) {
   return is_base_of<Base, T>::value;
}
    //references
    int i = 10;
    int& r=i;

    cout<<"i = "<<i<<endl;
    cout<<"r = "<<r<<endl;
    i=9;
    
    cout<<"rfunc = "<<hamada()<<endl;
    time_t now = time(0);
    cout<<"time now "<<ctime(&now)<<endl;
    tm *gmtm = gmtime(&now);
    cout<<1900+(gmtm->tm_year)<<endl;
    cout<<1+(gmtm->tm_wday)<<endl;
*/
/*
int& hamada(){
    int i= 1210;
    int& r = i;
    return r;
}*/
    return 0;
}

