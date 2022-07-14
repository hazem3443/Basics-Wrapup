#include <map>
#include <limits>
#include <cassert>
#include <vector>
#include <stdlib.h>
#include <iostream>
 
template<typename K, typename V>
class interval_map {
protected:
    std::map<K, V> m_map;
 
public:
    // constructor associates whole range of K with val by inserting (K_min, val)
    // into the map
    interval_map(V const& val) {
        m_map.insert(m_map.end(), std::make_pair(std::numeric_limits<K>::lowest(), val));
//  for (auto i = m_map.begin(); i!= m_map.end(); i++) {
//         std::cout <<"size = "<< m_map.size() <<" key is "<< i->first << "\t val is" << i->second << std::endl;
//     }
    }
 
    // Assign value val to interval [keyBegin, keyEnd).
    // Overwrite previous values in this interval.
    // Conforming to the C++ Standard Library conventions, the interval
    // includes keyBegin, but excludes keyEnd.
    // If !( keyBegin < keyEnd ), this designates an empty interval,
    // and assign must do nothing.
    void assign(K const& keyBegin, K const& keyEnd, V const& val) {
        if (!(keyBegin < keyEnd))
            return;
        auto nextInterval = --m_map.upper_bound(keyEnd);
        auto inserted1 = m_map.end();
        auto inserted2 = m_map.end();
        assert(nextInterval != m_map.end());
        if (nextInterval->second == val)
            ++nextInterval;
        else if (nextInterval->first < keyEnd)
        {
            const V & nextValue = nextInterval->second;
            ++nextInterval;
            inserted1 = nextInterval = m_map.emplace_hint(nextInterval, keyEnd, nextValue);
        }
        try
        {
            auto prevInterval = nextInterval;
            --prevInterval;
            assert(prevInterval != m_map.end());
            if (keyBegin < prevInterval->first)
                prevInterval = --m_map.upper_bound(keyBegin);
            assert(prevInterval != m_map.end());
            if (!(prevInterval->second == val))
            {
                if (prevInterval->first < keyBegin)
                {
                    ++prevInterval;
                    inserted2 = prevInterval = m_map.emplace_hint(prevInterval, keyBegin, val);
                }
                else
                {
				    prevInterval->second = val;
				    if (prevInterval != m_map.begin() && !((--prevInterval)->second == val))
				    {
				        ++prevInterval;
				    }
                }
            }
            assert(prevInterval != m_map.end());
            m_map.erase(++prevInterval, nextInterval);
        }
        catch (...)
        {
            if (inserted1 != m_map.end())
                m_map.erase(inserted1);
            if (inserted2 != m_map.end())
                m_map.erase(inserted2);
            throw;
        }
    }
 
    // look-up of the value associated with key
    V const& operator[](K const& key) const {
        return (--m_map.upper_bound(key))->second;
    }
};
 
class test_map : interval_map<unsigned char, unsigned char>
{
public:
    std::vector<unsigned char> m_check;
    test_map() : interval_map(16)
    {
        m_check.resize(256, 16);
    }
    void assign(unsigned char first, unsigned char last, unsigned char value)
    {
        test();
        interval_map::assign(first, last, value);
        for (int i = first; i < last; ++i)
            m_check[i] = value;
        test();
    }
    void test()
    {
        auto prev_it = m_map.begin();
        assert(!m_map.empty());
        assert(prev_it->first == 0);
        for (auto it = ++m_map.begin(); it != m_map.end(); ++it)
        {
            assert(prev_it->second != it->second);
            for (int i = prev_it->first; i < it->first; ++i)
                assert(m_check[i] == prev_it->second);
            prev_it = it;
        }
        for (int i = prev_it->first; i < 256; ++i)
            assert(m_check[i] == prev_it->second);
    }
};
 
// Many solutions we receive are incorrect. Consider using a randomized test
// to discover the cases that your implementation does not handle correctly.
// We recommend to implement a test function that tests the functionality of
// the interval_map, for example using a map of unsigned int intervals to char.
 
int main()
{
    for (int t = 0; t < 300; ++t)
    {
        test_map tm;
        for (int i = 0; i < 1000; ++i)
        {
            tm.assign(rand() % 256, rand() % 256, rand() % 16);
        }
        tm.test();
    }
    return 0;
}