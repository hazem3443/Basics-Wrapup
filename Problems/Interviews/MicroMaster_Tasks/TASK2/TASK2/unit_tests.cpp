#include <unistd.h>

#include "Result.h"
#include "acutest.hpp"
/*-----------------------------------readJson method--------------------------*/
void readJson_test_return_type(void){
    Result obj;
    TEST_CHECK_(typeid(obj.readJson("topology.json"))==typeid(Result), "-> readJson() return type is not of Result type" );
}

/*---extend Result class implemntation to test internal functionality---*/
//test internal object type successfully 
class readJson_test:public Result{
public:
    readJson_test(){
    }
    ~readJson_test(){
    }
    Json::Value topologyJson_obj(){// expose Json Object to test its content
        return this->_topologyJson_obj;
    }
};

void Test_readJson_internal_obj_type(){
    readJson_test obj;
    obj.readJson("topology.json");
    TEST_CHECK_( typeid(obj.topologyJson_obj()) == typeid(Json::Value), "-> .readJson('topology.json') internal Json object type is not of Json::Value type" );
}

void Test_readJson_internal_obj_loaded(){
    readJson_test obj;
    obj.readJson("topology.json");
    TEST_CHECK_( obj.topologyJson_obj() != (void*)NULL, "-> .readJson('topology.json') internal Json object is not loaded" );
}

/*------------------------------writeJson method--------------------------------*/
void writeJson_test_return_type(void){
    Result obj;
    obj.readJson("topology.json");
    TEST_CHECK_(typeid(obj.writeJson("new_topology.json"))==typeid(Result), "-> .writeJson('new_topology.json') return type is not of type Result" );
}

class writeJson_test:public Result{
public:
    writeJson_test(){
    }
    ~writeJson_test(){
    }
    Json::Value topologyJson_obj(){// expose Json Object to test its content
        return this->_topologyJson_obj;
    }
};

void writeJson_test_wrote_to_disk(void){
    Result obj;
    obj.readJson("topology.json");
    obj.writeJson("new_topology.json");
    TEST_CHECK_(access("new_topology.json", F_OK ) != -1, "-> .writeJson('new_topology.json') failed writing object to the disk" );
}

/*------------------------------deleteTopology method--------------------------------*/
void deleteTopology_test_return_type(void){
    Result obj;
    obj.readJson("topology.json");
    TEST_CHECK_(typeid(obj.deleteTopology("top1"))==typeid(Result), "-> .deleteTopology('top1') return type is not of type Result" );
}

class deleteJson_test:public Result{
public:
    deleteJson_test(){
    }
    
    ~deleteJson_test(){
    }

    Json::Value topologyJson_obj(){
        return this->_topologyJson_obj;
    }
};

void deleteTopology_test_item_deletion_functionality(void){
    deleteJson_test obj;
    obj.readJson("topology.json");
    //this file contains 2 topologies after deletion it would be top2 only
    obj.deleteTopology("top1");
    //check "top1" topology existence in the list
    for(int i=0;i<obj.topologyJson_obj().size();i++){
        TEST_CHECK_((obj.topologyJson_obj()[i]["id"].compare("top1")!=0), "-> .deleteTopology('top1') failed to delete Topology " );
    }
}

/*--------------------------queryTopologies method------------------------------*/
void queryTopologies_test_return_type(void){
    Result obj;
    obj.readJson("topology.json");
    TEST_CHECK_(typeid(obj.queryTopologies())==typeid(TopologyList), "-> .queryTopologies() return type is not of type TopologyList" );
}

class queryTopologies_test:public Result{
public:
    queryTopologies_test(){
    }
    
    ~queryTopologies_test(){
    }

    Json::Value topologyJson_obj(){
        return this->_topologyJson_obj;
    }
    TopologyList TopologiesList(){
        return this->_TopologiesList;
    }
};

void queryTopologies_test_loading_functionality(void){
    queryTopologies_test obj;
    obj.readJson("topology.json");
    
    int i;
    for(i=0;i<obj.topologyJson_obj().size();i++);

    TEST_CHECK_( (obj.queryTopologies().size() == i )&& (obj.TopologiesList().size() == i), "-> .queryTopologies() failed loading TopologyList" );
}

/*------------------------------queryDevices method--------------------------------*/
void queryDevices_test_return_type(void){
    Result obj;
    obj.readJson("topology.json");
    TEST_CHECK_(typeid(obj.queryDevices("top1"))==typeid(DeviceList), "-> .queryDevices('top1') return type is not of type DeviceList" );
}

class queryDevices_test:public Result{
public:
    queryDevices_test(){
    }
    
    ~queryDevices_test(){
    }

    Json::Value topologyJson_obj(){
        return this->_topologyJson_obj;
    }
    DeviceList DevicesList(){
        return this->_DevicesList;
    }
};

void queryDevices_test_devices_validation_in_selected_topology(void){
    queryDevices_test obj;
    obj.readJson("topology.json");
    DeviceList dlist = obj.queryDevices("top1");

    int i;
    for(i=0;i<obj.topologyJson_obj().size();i++){
        if(obj.topologyJson_obj()[i]["id"].compare("top1") == 0 )break;
    }

    for(int j=0;j<dlist.size();j++){
        TEST_CHECK_( (obj.topologyJson_obj()[i]["components"][j]["id"] == dlist[j].id() )&&
            (obj.topologyJson_obj()[i]["components"][j]["type"] == dlist[j].type()) ,"-> .queryDevices('top1') failed loading Devices in this topology" );
    }
}

/*------------------------------queryDevicesWithNetlistNode method--------------------------------*/
void queryDevicesWithNetlistNode_test_return_type(void){
    Result obj;
    obj.readJson("topology.json");
    TEST_CHECK_(typeid(obj.queryDevicesWithNetlistNode("top1","vdd"))==typeid(DeviceList), "return type is not of type DeviceList" );
}

class queryDevicesWithNetlistNode_test:public Result{
public:
    queryDevicesWithNetlistNode_test(){
    }
    
    ~queryDevicesWithNetlistNode_test(){
    }

    Json::Value topologyJson_obj(){
        return this->_topologyJson_obj;
    }
    DeviceList DevicesList(){
        return this->_DevicesList;
    }
};

void queryDevicesWithNetlistNode_test_devices_had_netlist_node(void){
    queryDevicesWithNetlistNode_test obj;
    obj.readJson("topology.json");
    DeviceList dlist = obj.queryDevicesWithNetlistNode("top1","vdd");
    
    TEST_CHECK_( (dlist.size() == 1) && 
        (dlist[0].id().compare("res1") == 0) &&
        (dlist[0].type().compare("resistor") == 0) ,
            "-> .queryDevicesWithNetlistNode('top1','vdd') return Device list doesn't match actual netlist" );
    
    TEST_CHECK_( (obj.topologyJson_obj()[0]["id"].asString().compare("top1") == 0) &&
        (obj.topologyJson_obj()[0]["components"][0]["netlist"]["t1"].compare("vdd") == 0 ),
         "-> .queryDevicesWithNetlistNode('top1','vdd') return Device list doesn't match actual netlist" );
}

TEST_LIST = {
    {"-> readJson() return type is Result type ",readJson_test_return_type},
    {"-> readJson() internal Json object type is Json::Value type ",Test_readJson_internal_obj_type},
    {"-> readJson() internal Json object is loading ",Test_readJson_internal_obj_loaded},
    
    {"-> writeJson() return type is Result type ",writeJson_test_return_type},
    {"-> writeJson() file wrote to disk functionality ",writeJson_test_wrote_to_disk},
    
    {"-> deleteTopology() return type is Result type ",deleteTopology_test_return_type},
    {"-> deleteTopology() item delettion functionality " ,deleteTopology_test_item_deletion_functionality},
    
    {"-> queryTopologies() return type is TopologyList type ",queryTopologies_test_return_type},
    {"-> queryTopologies() TopologyList loading ",queryTopologies_test_loading_functionality},

    {"-> queryDevices() return type is DeviceList type ",queryDevices_test_return_type},
    {"-> queryDevices() DeviceList loading ",queryDevices_test_devices_validation_in_selected_topology},

    {"-> queryDevicesWithNetlistNode() return type is DeviceList type ",queryDevicesWithNetlistNode_test_return_type},
    {"-> queryDevicesWithNetlistNode() return Device List validation on netlist node connection ",queryDevicesWithNetlistNode_test_devices_had_netlist_node},
    {0}
};