#ifndef TOPOLOGY_H_   /* Include guard */
#define TOPOLOGY_H_

#include <string>
#include <vector>
#include "Component.h"

using namespace std;

class topology_type{
private:
    string _id;
    //TODO:can be extended to more serialization reliability as and object model
    // vector<Component_type> components; 
public:
    topology_type();
    ~topology_type();

    string id();//getter for class property
    void set_id(string);//setter for class property
};

#endif