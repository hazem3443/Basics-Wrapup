#include <iostream>

using namespace std;

int x = 20;

class human{
    public:
        string name;
        string country;
        int age;

        human(string name, string country, int age){
            human::name = name;
            human::country = country;
            human::age = age;
        }
        ~human(){
            cout << "human "<<human::name << " destroyed" << endl;
        }
};

#pragma omp parallel num_threads(2)
int main(){
    human hazem("hazem","Egypt",26);
    human ahmed();

    cout << "name : " << hazem.name << endl;
    // delete (void*)&hazem;
    // hazem.~human();
    // delete hazem;
    // delete[] (void*)&hazem;
    #pragma omp flush()

    cout << "Point"<<endl;
    return 0;
}

