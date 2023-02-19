#pragma once
#ifndef Event_hpp
#define Event_hpp

#include <stdio.h>
#include <string>
#include "core/Vector2.h"

using namespace std;

class Event
{
public:
    
    Event() { initializeMembers(); };
	Event(const string& eventName) { initializeMembers(); m_eventName = eventName; };
    Event(const string& eventName, void* pParam) { initializeMembers(); m_eventName = eventName; m_pParam = pParam;}
    Event(const string& eventName, int iData) { initializeMembers(); m_eventName = eventName; m_iData = iData;}
    ~Event() {};
    
    const string& getName() const { return m_eventName; };
    void setName(const string& eventName) { m_eventName = eventName; };
    
    void setParam(void* pParam) { m_pParam = pParam; };
    void* getParam() const { return m_pParam; };

    const int getData() const { return m_iData; };
    void setData(int iData) { m_iData = iData; };

    const float getFloatData() const { return m_fData; };
    void setFloatData(float fData) { m_fData = fData; };

    const Vector2& getInputCoordinates() const { return m_inputCoordinates; };
    void setInputCoordinates(const Vector2& inputCoordinates) { m_inputCoordinates = inputCoordinates; };

    void setTarget(const string& target) { this->m_target = target; };
    const string& getTarget() const { return m_target; };

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
