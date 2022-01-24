#include "API.h"
#include <iostream>
#include <string>
#include <fstream>
#include <jsoncpp/json/json.h>

using namespace std;

Result Result::readJSON(string FileName){
    
    ifstream topologyJson_file("topology.json", std::ifstream::binary);
    topologyJson_file >> this->topologyJson_obj;
    /*
    int i = 0;
    Result *res = new Result();

    while(i<MAX_Topologiess_For_returnResult){
        // cout<<FileName+to_string(i)<<endl;
        res->tops[i] = new topology_type(FileName+to_string(i));
        i++;
    }
    return res;
    */
}

