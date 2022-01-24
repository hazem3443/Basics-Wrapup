#include "Component.h"

Component_type::Component_type(){

}
Component_type::~Component_type(){

}

string Component_type::id(){
    return this->_id;
}
void Component_type::set_id(string id){
    this->_id = id;
}

string Component_type::type(){
    return this->_type;
}
void Component_type::set_type(string type){
    this->_type = type;
}