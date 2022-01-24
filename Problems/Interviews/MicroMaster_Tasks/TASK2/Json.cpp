#include <iostream>
#include <fstream>
#include <jsoncpp/json/json.h>
#include "API.h"

using namespace std;

int main()
{
    /*
    topology_type Top1("top1");

    cout<<Top1.id<<endl;
    
    Resistor_type R1;
    R1.type = "resistor";
    R1.id = "res1";
    R1.resistance._default = 100;
    R1.resistance.min_value = 10;
    R1.resistance.max_value = 1000;
    R1.netlist_set("vdd","n1");
    
    cout<<"R1 type::\t"<< R1.type <<endl;
    cout<<"R1 id::\t"<< R1.id <<endl;
    cout<<"R1 resistance.default::\t"<< R1.resistance._default <<endl;
    cout<<"R1 resistance.min::\t"<< R1.resistance.min_value<<endl;
    cout<<"R1 resistance.max::\t"<< R1.resistance.max_value<<endl;
    cout<<"R1 resistance.netlist.t1::\t"<< R1.netlist.t1 <<endl;
    cout<<"R1 resistance.netlist.t2::\t"<< R1.netlist.t2 <<endl;

    Top1.components[0] = &R1;

    cout<<"T1.components[0] type::\t"<< Top1.components[0]->type <<endl;
    cout<<"T1.components[0] id::\t"<< Top1.components[0]->id <<endl;
    cout<<"T1.components[0] resistance.default::\t"<< ((Resistor_type*)Top1.components[0])->resistance._default <<endl;
    cout<<"T1.components[0] resistance.min::\t"<< ((Resistor_type*)Top1.components[0])->resistance.min_value<<endl;
    cout<<"T1.components[0] resistance.max::\t"<< ((Resistor_type*)Top1.components[0])->resistance.max_value<<endl;
    cout<<"T1.components[0] resistance.netlist.t1::\t"<< ((Resistor_type*)Top1.components[0])->netlist.t1 <<endl;
    cout<<"T1.components[0] resistance.netlist.t2::\t"<< ((Resistor_type*)Top1.components[0])->netlist.t2 <<endl;
*/
    
    // Result* r1;
    // r1 = readJSON("hamada");

    // cout<< ((topology_type*)r1->tops[0])->id <<endl;

    Json::Value topology;
    ifstream topologyJson_file("topology.json", std::ifstream::binary);
    topologyJson_file >> topology;

    // for(int i=0;i<;i++){}
    cout << topology[0]["id"] << "\n";
    cout << topology[1]["id"] << "\n";
    
    topology[0]["id"] = "topology1";
    topology[1]["id"] = "topology2";

    cout << topology[0]["id"] << "\n";
    cout << topology[1]["id"] << "\n";

    // topologyJson_file << topology;
    topologyJson_file.close();

    ofstream outputFile;
    outputFile.open ("JsonWrite.json");
    outputFile << topology<<endl;
    outputFile.close();

    return 0;
}