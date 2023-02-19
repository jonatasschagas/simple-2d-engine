#ifndef DataCache_hpp
#define DataCache_hpp

#include <stdio.h>
#include <map>
#include <string>
#include <vector>

using namespace std;

template<class T>
class DataCache
{
public:
    
    DataCache()
    {
        initializeMembers();
    }
    
    ~DataCache()
    {
        for( auto it = m_dataMap.begin(); it != m_dataMap.end(); ++it )
        {
            auto p = it->second;
            delete p;
            p = nullptr;
        }
        
        initializeMembers();
    }
    
    T* getData(const string& configName)
    {
        auto it = m_dataMap.find(configName);
        T* t = nullptr;
        if(it == m_dataMap.end())
        {
            //element not found;
            t = new T(configName);
            m_dataMap[configName] = t;
            m_items.push_back(t);
        }
        else
            t = m_dataMap[configName];
        
        return t;
    }
    
    T* getData(const string& f1, const string& f2)
    {
        string key = f1 + ":" + f2;
        auto it = m_dataMap.find(key);
        T* t = nullptr;
        if(it == m_dataMap.end())
        {
            //element not found;
            t = new T(f1, f2);
            m_dataMap[key] = t;
        }
        else
            t = m_dataMap[key];
        
        return t;
    }
    
    vector<T*> getItems()
    {
        return m_items;
    }
    
private:
    
    map<string,T*> m_dataMap;
    vector<T*> m_items;
    
    void initializeMembers()
    {
        m_dataMap.clear();
        m_items.clear();
    }
    
};

#endif /* DataCache_hpp */
