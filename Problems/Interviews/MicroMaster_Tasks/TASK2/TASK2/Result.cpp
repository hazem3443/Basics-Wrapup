#include "Result.h"

Result::Result(){

}

Result::~Result(){

}

Result Result::readJson(string FileName){
    /*create file stream and reads json file into map object of type Json:Value then return "this" as 
    a new initialized object from "this" pointer */
    ifstream topologyJson_file(FileName, std::ifstream::binary);
    topologyJson_file >> this->_topologyJson_obj;
    topologyJson_file.close();
    return *this;
}

Result Result::writeJson(string FileName){
    /*open file stream with the new 'FileName' and write our mapped object to it then return "this" object*/
    ofstream outputFile;
    outputFile.open(FileName);
    outputFile << this->_topologyJson_obj<<endl;
    outputFile.close();//close file
    return *this;        
}

Result Result::deleteTopology(string TopologyID){
    Json::Value newArray = Json::arrayValue;//create new array of type Json::Value
    for (Json::ValueIterator itr_any = this->_topologyJson_obj.begin(); itr_any != this->_topologyJson_obj.end(); ++itr_any)
        /*loop over topologies*/
        if (0 != (*itr_any)["id"].asString().compare(TopologyID))
        {/*if deleted topology id found ignore appedning it to our array*/
            newArray.append((*itr_any));//append object to our array
        }
    this->_topologyJson_obj = newArray;//save new map to our main object map
    return *this;//return object reference of the same type
}

TopologyList Result::queryTopologies(){
    TopologyList result;//create new array of type TopologyList
    for (Json::ValueIterator itr_topologies = this->_topologyJson_obj.begin(); itr_topologies != this->_topologyJson_obj.end(); ++itr_topologies){
        /*loop over topology map*/
        topology_type* tx = new topology_type();//allocate new topology type which is the item type of each topologyList item
        tx->set_id( (*itr_topologies)["id"].asString() );//set new topology id to selected topology item 
        result.push_back(*tx);//save it to our list
    }
    this->_TopologiesList = result;//assign our list to topology list
    return this->_TopologiesList;//return referenc to TopologyList type
}

DeviceList Result::queryDevices(string TopologyID){
    DeviceList result;
    Json::Value newArray = Json::arrayValue;
    for (Json::ValueIterator itr_any = this->_topologyJson_obj.begin(); itr_any != this->_topologyJson_obj.end(); ++itr_any){
        /*loop over topology map*/
        if (0 == (*itr_any)["id"].asString().compare(TopologyID))
        {/*if selected map found */
            for (Json::ValueIterator component_any = (*itr_any)["components"].begin(); component_any != (*itr_any)["components"].end(); ++component_any){
                /*iterate over its components and save them to DevicesList "result" object*/
                Component_type* cx = new Component_type();
                cx->set_id((*component_any)["id"].asString());
                cx->set_type((*component_any)["type"].asString());
                result.push_back(*cx);
            }
        }
    }
    this->_DevicesList = result;//save our "result" object to DevicesList property local to our class
    return this->_DevicesList;//return reference to the DevicesList item
}
DeviceList Result::queryDevicesWithNetlistNode(string TopologyID,string NetlistNodeID){
    DeviceList result;
    for (Json::ValueIterator itr_any = this->_topologyJson_obj.begin(); itr_any != this->_topologyJson_obj.end(); ++itr_any)
        /*iterate over topologies*/
        if (0 == (*itr_any)["id"].asString().compare(TopologyID))//if find selected topology
            for (Json::ValueIterator component_any = (*itr_any)["components"].begin(); component_any != (*itr_any)["components"].end(); ++component_any)
                /*iterate over components*/
                for (Json::ValueIterator it = (*component_any)["netlist"].begin(); it != (*component_any)["netlist"].end(); ++it)
                    /*iterate over netlist items*/
                    if(0 == (*component_any)["netlist"][it.name()].asString().compare(NetlistNodeID)){
                        /*if find that netlist node id then save the component to the "result" list*/
                        Component_type* cx = new Component_type();
                        cx->set_id((*component_any)["id"].asString());
                        cx->set_type((*component_any)["type"].asString());
                        result.push_back(*cx);
                        break;//break to prevent multi nodes assigned to certain node for the same component
                    }

    this->_DevicesList = result;
    return this->_DevicesList;//return object of DevicesList type containing the devices connected to certain nodeId
}

// Json::Value Result::topologyJson_obj(){
//     return this->_topologyJson_obj;
// }
// TopologyList Result::TopologiesList(){
//     return this->_TopologiesList;
// }
// DeviceList Result::DevicesList(){
//     return this->_DevicesList;
// }