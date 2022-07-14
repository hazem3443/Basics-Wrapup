#include <map>
#include <iostream>

using namespace std;

template<typename K, typename V>
class interval_map {
	friend void IntervalMapTest();
	V m_valBegin;
	std::map<K,V> m_map;
public:
	// constructor associates whole range of K with val
	interval_map(V const& val)
	: m_valBegin(val)
	{}

	// Assign value val to interval [keyBegin, keyEnd).
	// Overwrite previous values in this interval.
	// Conforming to the C++ Standard Library conventions, the interval
	// includes keyBegin, but excludes keyEnd.
	// If !( keyBegin < keyEnd ), this designates an empty interval,
	// and assign must do nothing.
	void assign( K const& keyBegin, K const& keyEnd, V const& val ) {
		// INSERT YOUR SOLUTION HERE
        /*The function assign should insert the interval [keyBegin, keyEnd] with val into the m_map.*/        

        if (!(keyBegin < keyEnd))
            return;
        //insert first dummy value to the map if it is empty
        if(m_map.size() == 0 )
            m_map.insert( {std::numeric_limits<K>::lowest(), this->m_valBegin} );
        
        //with empty map this will be the dummy value,then we will validate 
        auto next = --m_map.upper_bound(keyEnd);
        
        /* insert keyEnd item then update next iterator*/
        //if inserted val is the same as the default val move to next item 
        if (m_valBegin == val)
            ++next;
        //if left intersection occur then insert val to keyEnd->val
        else if (next->first < keyEnd)
            //keep the value of left intersect to be deleted element
            next = m_map.emplace_hint(m_map.end(), keyEnd, next->second);//insert end of the interval to be inserted
        
        /* insert keyBegin item then erase useless item*/
        // move to the previoud of last element in the map
        auto prev = next;
        --prev;
        if (keyBegin < prev->first)
            prev = --m_map.upper_bound(keyBegin);
        
        if (!(prev->second == val)){
            if (prev->first < keyBegin)
                prev = m_map.emplace_hint(m_map.end(), keyBegin, val);//insert start of the interval to be inserted
            else
            {
                prev->second = val;
                if (prev != m_map.begin() && !((--prev)->second == val))
                    ++prev;
            }
        }
        m_map.erase(++prev, next);
        
	}

	// look-up of the value associated with key
	V const& operator[]( K const& key ) const {
		auto it=m_map.upper_bound(key);
		if(it==m_map.begin()) {
			return m_valBegin;
		} else {
			return (--it)->second;
		}
	}
};


#include <string>
int count = 18;
interval_map<int, string> im("\033[91mR");

int show_interval(int from, int to, string val){
    im.assign(from, to, val);
    for (size_t i = 0; i < count; i++)
        cout<<im[i]<<"\t";
    cout<<endl;
    return 1;
}

void IntervalMapTest() {

    show_interval(2,8, "\033[91mR");    

    show_interval(2,8, "\033[36mB");    
    show_interval(6, 10, "\033[92mG");
    show_interval(1, 5, "\033[93mY");
    show_interval(3, 7, "\033[35mP");
    show_interval(11, 13, "\033[35mP");
    show_interval(11, 13, "\033[35mBX");
    show_interval(11, 15, "\033[35mBX");

    show_interval(1,10, "\033[91mR");    


    for (size_t i = 0; i < count; i++)
        cout<<"\033[97m"<<i<<"\t";
    cout<<endl;    
}



int main() {
    IntervalMapTest();
    return 0;
}

