//data structure --std=C++17
#include <iostream>
#include <map>
#include <limits>
#include <cassert>
#include <vector>
#include <stdlib.h>

using namespace std;

template <typename T>
class Node {
public:
    T data;
    Node* next;
    Node(T data) {
        this->data = data;
        this->next = NULL;
    }
};

template <typename T>
class LinkedList {
public:
    Node<T>* head;
    LinkedList() {
        this->head = NULL;
    }
    void add(T data) {
        Node<T>* newNode = new Node<T>(data);
        if (this->head == NULL) {
            this->head = newNode;
        } else {
            Node<T>* temp = this->head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }
    void print() {
        Node<T>* temp = this->head;
        while (temp != NULL) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

int main() {
    LinkedList<int> list;
    list.add(1);
    list.add(2);
    list.add(3);
    list.add(4);
    // list.print();

    cout<<std::numeric_limits<unsigned char>::min()<<endl;
    return 0;
}




//check the start < end and if not, return.
        // if(!(keyBegin < keyEnd))
        //     return;
        // //insert first elements in the map
        // if(!m_map.size()){
        //     m_map.insert(m_map.begin(), make_pair(keyBegin, val));
        //     m_map.insert(m_map.begin(), make_pair(keyEnd, m_valBegin));

        // }
        // else{
        //     //find the intersection of keyEnd and keyBegin
            

        //     auto e_up = m_map.upper_bound(keyEnd);
        //     auto e_low = --m_map.lower_bound(keyEnd);

        //     cout << "upper -> "<< e_up->first << "\t" << e_up->second << endl;
        //     cout << "lower -> "<< e_low->first << "\t" << e_low->second << endl;

        //     if(e_up != m_map.end() && e_up->first > keyEnd)
        //     {
        //         m_map.insert(m_map.begin(), make_pair(keyEnd, e_low->second));
        //         m_map.insert(m_map.begin(), make_pair(keyBegin, val));
                
        //         m_map.erase(e_low->first);
        //     }

        //     else if(e_low != m_map.end() && e_low->first < keyBegin)
        //     {
        //         m_map.insert(m_map.begin(), make_pair(keyBegin, --e_up->second));
        //         m_map.insert(m_map.begin(), make_pair(keyEnd, val));

        //         m_map.erase(e_up->first);
        //     }
        //     else{
        //         m_map.insert(m_map.begin(), make_pair(keyBegin, val));
        //         m_map.insert(m_map.begin(), make_pair(keyEnd, m_valBegin));
        //     }

        //     for (auto i = m_map.begin(); i!= m_map.end(); i++) {
        //         cout << i->first << "\t" << i->second << endl;
        //     }

        //     return;

        // }