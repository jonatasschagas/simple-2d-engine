#ifndef DataCache_hpp
#define DataCache_hpp

#include "platform/ResourceProvider.hpp"
#include <map>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

template <class T>
class DataCache {
 public:
  DataCache(ResourceProvider& rResourceProvider)
      : m_rResourceProvider(rResourceProvider) {
    initializeMembers();
  }

  ~DataCache() {
    for (auto it = m_items.begin(); it != m_items.end(); ++it) {
      delete *it;
    }

    initializeMembers();
  }

  T const& getData(string const& configName) {
    auto it = m_dataMap.find(configName);
    if (it == m_dataMap.end()) {
      string configValue = "";
      m_rResourceProvider.readContentsFromFile(configName, &configValue);
      // element not found;
      T* t = new T(configValue);
      m_dataMap[configName] = t;
      m_items.push_back(t);
    }

    return *m_dataMap[configName];
  }

  T const& getData(string const& f1, string const& f2) {
    string key = f1 + ":" + f2;
    auto it = m_dataMap.find(key);

    if (it == m_dataMap.end()) {
      // element not found;
      string const& configPath = f1;
      string configValue = "";
      m_rResourceProvider.readContentsFromFile(configPath, &configValue);

      T* t = new T(configValue, f2);
      m_dataMap[key] = t;
    }

    return *m_dataMap[key];
  }

  T const& getData(string const& f1, string const& f2, string const& f3) {
    string key = f1 + ":" + f2 + ":" + f3;
    auto it = m_dataMap.find(key);

    if (it == m_dataMap.end()) {
      // element not found;
      T* t = new T(f1, f2, f3, m_rResourceProvider);
      m_dataMap[key] = t;
    }

    return *m_dataMap[key];
  }

  vector<T> const& getItems() { return m_items; }

 private:
  map<string, T*> m_dataMap;
  vector<T*> m_items;
  ResourceProvider& m_rResourceProvider;

  void initializeMembers() {
    m_dataMap.clear();
    m_items.clear();
  }
};

#endif /* DataCache_hpp */
