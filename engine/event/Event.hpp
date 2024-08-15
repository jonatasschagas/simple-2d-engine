#pragma once
#ifndef Event_hpp
#define Event_hpp

#include "core/Vector2.h"
#include <stdio.h>
#include <string>

using namespace std;

class Event {
 public:
  Event() { initializeMembers(); };
  explicit Event(string const& eventName) {
    initializeMembers();
    m_eventName = eventName;
  };
  Event(string const& eventName, void* pParam) {
    initializeMembers();
    m_eventName = eventName;
    m_pParam = pParam;
  }
  Event(string const& eventName, int iData) {
    initializeMembers();
    m_eventName = eventName;
    m_iData = iData;
  }
  ~Event() {};

  string const& getName() const { return m_eventName; };
  void setName(string const& eventName) { m_eventName = eventName; };

  void setParam(void* pParam) { m_pParam = pParam; };
  void* getParam() const { return m_pParam; };

  int const getData() const { return m_iData; };
  void setData(int iData) { m_iData = iData; };

  float const getFloatData() const { return m_fData; };
  void setFloatData(float fData) { m_fData = fData; };

  Vector2 const& getInputCoordinates() const { return m_inputCoordinates; };
  void setInputCoordinates(Vector2 const& inputCoordinates) {
    m_inputCoordinates = inputCoordinates;
  };

  void setTarget(string const& target) { this->m_target = target; };
  string const& getTarget() const { return m_target; };

  void clone(Event* pOther) {
    m_eventName = pOther->getName();
    m_pParam = pOther->getParam();
    m_iData = pOther->getData();
    m_target = pOther->getTarget();
    m_inputCoordinates = pOther->getInputCoordinates();
  }

 private:
  string m_target;
  string m_eventName;
  void* m_pParam;
  int m_iData;
  float m_fData;
  Vector2 m_inputCoordinates;

  void initializeMembers() {
    m_pParam = nullptr;
    m_iData = -1;
    m_fData = -1;
    m_target = "";
    m_inputCoordinates = Vector2(0, 0);
    m_eventName = "";
  }
};

#endif /* Event_hpp */
