#include <iostream>
#include <sstream>  
#include <string>
#include <vector>
#include <cstring>
#include <bits/stdc++.h>

#include <vector>
#include <string>

class PacketReceiver {
public:
    void StartPacket();

    bool ReceivePart(uint16_t id, size_t controlSum, const std::string& data);

    std::vector<std::string> GetCollectedPackets() const;

    size_t GetNumOfFailedParts() const;

private:
    int numof_failed_parts = 0;
    std::vector< std::map<int,std::string> > packet_index;
    std::vector<int> current_started_pks;
};

using namespace std;

int main(){
    hash<string> compute_hash;

    PacketReceiver rec;
    rec.StartPacket();
    rec.StartPacket();
    // rec.ReceivePart(1, compute_hash("HelloWorldDuplicates"), "HelloWorldDuplicates");

    auto packets = rec.GetCollectedPackets();
    // packet.size() should be 2
    // packets[0] should be ""
    // packets[1] should be ""

    for(auto pk: packets){
        cout <<"packet" <<pk << endl;
    }
    // ///////////////////////
    // PacketReceiver rec2;
    // rec2.StartPacket();
    // rec2.ReceivePart(1, std::hash<std::string>{}("World"), "World");
    // rec2.ReceivePart(0, std::hash<std::string>{}("Hello "), "Hello ");
    // rec2.ReceivePart(2, std::hash<std::string>{}("!"), "!");

    // auto packets2 = rec2.GetCollectedPackets();
    // packet.size() should be 1
    // packets[0] should be "Hello World!"
    // rec.GetNumOfFailedParts() should return 0

    // // call it again:
    // auto anotherTry = rec2.GetCollectedPackets();
    // // packets == anotherTry

    // //////////////////////////////////////
    // PacketReceiver rec3;

    // rec3.StartPacket();
    // rec3.ReceivePart(1, std::hash<std::string>{}("World"), "World");
    // rec3.ReceivePart(0, std::hash<std::string>{}("Hello "), "Hello ");
    // rec3.ReceivePart(2, std::hash<std::string>{}("!"), "!");

    // rec3.StartPacket();
    // rec3.ReceivePart(100, std::hash<std::string>{}("Packet"), "Packet");
    // rec3.ReceivePart(101, std::hash<std::string>{}("Receiver"), "Receiver");

    // auto packets = rec3.GetCollectedPackets();
    // // packet.size() should be 2
    // // packets[0] should be "Hello World!"
    // // packets[1] should be "PacketReceiver"
    // // rec.GetNumOfFailedParts() should return 0
    
    // /////////////////////////////
    // PacketReceiver rec4;

    // rec4.StartPacket();
    // rec4.ReceivePart(1, std::hash<std::string>{}("World"), "World");
    // rec4.ReceivePart(0, std::hash<std::string>{}("Hello "), "Hello ");
    // rec4.ReceivePart(2, std::hash<std::string>{}("!"), "!");

    // rec4.StartPacket();
    // rec4.ReceivePart(100, std::hash<std::string>{}("Packet"), "Packet");
    // rec4.ReceivePart(101, std::hash<std::string>{}("Receiver"), "Receiver");

    // auto packets = rec4.GetCollectedPackets();
    // packet.size() should be 2
    // packets[0] should be "Hello World!"
    // packets[1] should be "PacketReceiver"
    // rec.GetNumOfFailedParts() should return 0
    // cout<<"Hello World"<<endl;
}

void PacketReceiver::StartPacket() {
    //prepare a new packet
    std::map<int,std::string> new_packet;
    packet_index.push_back(new_packet);
}

bool PacketReceiver::ReceivePart(uint16_t id, size_t controlSum, const std::string& data) {
    //check if the packet is already started
    if(packet_index.size() == 0){
        return false;
    }
    //check control sum
    if(controlSum != std::hash<std::string>{}(data)){
        numof_failed_parts++;
        return false;
    }
    //check if id exists
    if(packet_index[packet_index.size()-1].find(id) != packet_index[packet_index.size()-1].end()){
        numof_failed_parts++;
        return false;
    }
    //add the data to the packet_index map
    packet_index[packet_index.size()-1][id] = data;
    return true;
}

std::vector<std::string> PacketReceiver::GetCollectedPackets() const {
    std::cout << "this is my debug message \n";
    //check current started packets
    std::vector<std::string> collected_packets;
    for(auto packet: packet_index){
        std::string collected_packet = "";
        for(auto data: packet){
            collected_packet += data.second;
        }
        collected_packets.push_back(collected_packet);
    }
    return collected_packets;

}

size_t PacketReceiver::GetNumOfFailedParts() const {
    //return number of failed packets accross all packets
    return numof_failed_parts;
}