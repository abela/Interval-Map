
#include <iostream>
#include <map>
#include <limits>

template<typename K, typename V>
class interval_map {
    std::map<K,V> m_map;
    
public:
    interval_map( V const& val) {
        m_map.insert(m_map.end(),std::make_pair(std::numeric_limits<K>::lowest(),val));
    }
    
    void assign( K const& keyBegin, K const& keyEnd, V const& val ) {
        //
        // empty interval check
        if(keyEnd < keyBegin)
        {
            return;
        }
        //
        auto const lastElement = (--m_map.end());
        //
        // check canonical
        if(val == lastElement->second)
        {
            return;
        }
        
        K const min = lastElement->first < keyBegin ? lastElement->first : keyBegin;
        for(auto i = min; i < keyEnd; ++i)
        {
            m_map[i] = (i < keyBegin ? lastElement->second : val);
        }
    }
    
    // look-up of the value associated with key
    V const& operator[]( K const& key ) const {
        return ( --m_map.upper_bound(key) )->second;
    }
    
    void Print()
    {
        std::cout<<"map size is: "<<m_map.size()<<std::endl;
        for(auto element : m_map)
        {
            std::cout << element.first << " " << element.second << std::endl;
        }
    }
};

int main(int argc, const char * argv[]) {
    //
    interval_map<unsigned int, char> map('a');
    map.assign(6, 30, 't');
    map.assign(8, 12, 'd');
    map.assign(14, 25, 'm');
    map.Print();
    //
    return 0;
}
