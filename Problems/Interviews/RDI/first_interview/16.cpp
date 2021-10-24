#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unistd.h>

using namespace std;

int find_newtwork_endpoint(int startNodeId, vector<int> fromIds, vector<int> toIds);

int main() {
    cout << "Hellow World"<<endl;
    vector<int> fromIds = {0,1,2,3,4,5,6,7,0,9};
    vector<int> toIds   = {0,3,6,4,6,0,9,3,0,5};

    cout << find_newtwork_endpoint(1,fromIds, toIds)<<endl;
    cout << find_newtwork_endpoint(2,fromIds, toIds)<<endl;
    cout << find_newtwork_endpoint(3,fromIds, toIds)<<endl;
    cout << find_newtwork_endpoint(4,fromIds, toIds)<<endl;
    cout << find_newtwork_endpoint(5,fromIds, toIds)<<endl;
    cout << find_newtwork_endpoint(6,fromIds, toIds)<<endl;
    cout << find_newtwork_endpoint(7,fromIds, toIds)<<endl;
    cout << find_newtwork_endpoint(9,fromIds, toIds)<<endl;
    return 0;
}

int find_newtwork_endpoint(int startNodeId, vector<int> fromIds, vector<int> toIds) {
    int current_node=startNodeId;
    // int last_traversed_node;
    // last_traversed_node = 
    while(current_node != 0){
        //if current node in from and have toid
        //move to next node
        if(fromIds[current_node]!=0 && toIds[current_node] !=0 ){
            current_node=toIds[current_node];
        }
        else break;        
    }

    return current_node;
}