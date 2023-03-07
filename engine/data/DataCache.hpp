#ifndef DataCache_hpp
#define DataCache_hpp

#include <map>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

template <class T>
class DataCache {
 public:
  DataCache() { initializeMembers(); }

  ~DataCache() { initializeMembers(); }

  T const& getData(string const& configName) {
    auto it = m_dataMap.find(configName);
    if (it == m_dataMap.end()) {
      // element not found;
      T t(configName);
      m_dataMap[configName] = t;
      m_items.push_back(t);
    }

    return m_dataMap[configName];
  }

  T const& getData(string const& f1, string const& f2) {
    string key = f1 + ":" + f2;
    auto it = m_dataMap.find(key);

    if (it == m_dataMap.end()) {
      // element not found;
      T t(f1, f2);
      m_dataMap[key] = t;
    }

    return m_dataMap[key];
  }

  vector<T> const& getItems() { return m_items; }

 private:
  map<string, T> m_dataMap;
  vector<T> m_items;

  void initializeMembers() {
    m_dataMap.clear();
    m_items.clear();
  }
};

#endif /* DataCache_hpp */
