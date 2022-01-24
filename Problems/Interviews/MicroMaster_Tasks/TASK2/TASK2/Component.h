#ifndef COMPONENT_H_   /* Include guard */
#define COMPONENT_H_

#include <string>

using namespace std;

class Component_type{
private:
    string _id;
    string _type;
public:
    Component_type();
    ~Component_type();
    
    string id();//getter for class property
    void set_id(string id);//setter for class property
    
    string type();//getter for class property
    void set_type(string type);//setter for class property
};

#endif