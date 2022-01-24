#include <string>
#include <iostream>
#include <cstring>
#include <list>
#include <vector>
#include <jsoncpp/json/json.h>

/*----------------Main Class Structure--------------*/

#define MAX_Components_For_aTopology 10

using namespace std;

class Component_type{
public:
    string type;
    string id;
    Component_type(){

    }
    ~Component_type(){

    }

    virtual void netlist(){
        cout << "Component type"<<endl;
    }
};

class property_type{
public:
    int _default;
    int min_value;
    int max_value;
};

class Resistor_type:public Component_type{
public:
    property_type resistance;

    typedef struct {
        string t1;
        string t2;
    } res_netlist_type;
    
    res_netlist_type netlist;
    
    Resistor_type(){
        this->type = Component_type::type;
        this->id = Component_type::id;
    }
    ~Resistor_type(){

    }

    void netlist_set(string t1, string t2){
        // printf("set component type\n");
        this->netlist.t1 = t1;
        this->netlist.t2 = t2;
    }

    // Resistor();
    // ~Resistor();
};


class Nmos_type:public Component_type{
public:
    property_type m_1;

    typedef struct {
        string drain;
        string gate;
        string source;
    } Nmos_netlist_type;
    
    Nmos_netlist_type netlist;

    void netlist_set(string drain, string gate, string source){
        // printf("set component type\n");
        this->netlist.drain = drain;
        this->netlist.gate = gate;
        this->netlist.source = source;
    }

    // Nmos_type();
    // ~Nmos_type();
};

class topology_type{
public:
    string id;
    vector<Component_type> components;
    topology_type(string id){
        this->id = id;
    }
    ~topology_type(){

    }
};

/*------------------Main Return Types----------*/
#define MAX_Topologiess_For_returnResult 10

class DeviceList
{
private:
    /* data */
public:
    DeviceList(/* args */);
    ~DeviceList();
};

class TopologyList
{
private:
    /* data */
public:
    TopologyList(/* args */);
    ~TopologyList();
};

class Result
{
protected:
    Json::Value topologyJson_obj;

public:
    vector<topology_type> topologies;
    Result(){
    }
    ~Result(){
    }
    Result readJSON(string FileName);//
    Result writeJSON(string TopologyID);//
    TopologyList queryTopologies();
    Result deleteTopology(string TopologyID);//
    DeviceList queryDevices(string TopologyID);
    DeviceList queryDevicesWithNetlistNode(string TopologyID,string NetlistNodeID);
};


