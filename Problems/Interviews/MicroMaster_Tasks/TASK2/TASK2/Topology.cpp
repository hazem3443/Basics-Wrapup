#include "Topology.h"

topology_type::topology_type(){
}
topology_type::~topology_type(){
}
string topology_type::id(){
    return this->_id;
}
void topology_type::set_id(string id){
    this->_id = id;
}