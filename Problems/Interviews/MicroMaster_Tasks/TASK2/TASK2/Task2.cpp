#include "Result.h"

int main()
{
    Result R1;

    R1.readJson("topology.json");//read from "topology.json" file

    /*queryTopologies and save it in a TopologiyList type*/
    TopologyList ts = R1.queryTopologies();
    cout<<"------Query Topology List IDs------"<<endl;
    for(int i=0;i<ts.size();i++)
        cout<<"Topology ID -> "<<ts[i].id()<<endl;

    /*queryDevices and save it in a DeviceList type*/
    cout<<endl<<"------Query Device List ID & TYPE of certain Topology------"<<endl;
    DeviceList ds = R1.queryDevices("top1");
    for(int i=0;i<ds.size();i++)
        cout<<"Device ID -> "<<ds[i].id()<<" \tDevice TYPE -> "<<ds[i].type()<<endl;
    
    /*queryDevices connected to a certain netlist node and save it in a DeviceList type*/
    cout<<endl<<"------Query Device List connected to certain netlist node of certain Topology------"<<endl;
    DeviceList ds_with_n = R1.queryDevicesWithNetlistNode("top1","vin");
    for(int i=0;i<ds_with_n.size();i++)
        cout<<"Device ID -> "<<ds_with_n[i].id()<<" \tDevice TYPE -> "<<ds_with_n[i].type()<<endl;

    /*Delete a topology from the result object*/
    R1.deleteTopology("top2");

    /*Save topology object to Disk ("Write to "new_topology.json" file")*/
    R1.writeJson("new_topology.json");//

    return 0;
}

