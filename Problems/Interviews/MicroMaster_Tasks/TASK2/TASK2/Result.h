#ifndef RESULT_H_   /* Include guard */
#define RESULT_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <jsoncpp/json/json.h>
#include "Topology.h"

using namespace std;

typedef vector<topology_type> TopologyList;//Topology List Type
typedef vector<Component_type> DeviceList;//Device List Type

class Result {
protected:
    //class properties
    Json::Value _topologyJson_obj;//Json Object generated by jsoncpp 
    
    TopologyList _TopologiesList;//Topology Object
    DeviceList _DevicesList;//Device Object
public:

    Result readJson(string FileName);
    Result writeJson(string FileName);
    Result deleteTopology(string TopologyID);
    TopologyList queryTopologies();
    DeviceList queryDevices(string TopologyID);
    DeviceList queryDevicesWithNetlistNode(string TopologyID,string NetlistNodeID);

    /*internal properties getters for testing purposes*/
    // Json::Value topologyJson_obj();//Json Object generated by jsoncpp 
    // TopologyList TopologiesList();//Topology Object
    // DeviceList DevicesList();//Device Object

    Result();//constructor
    ~Result();//destructor
};

#endif