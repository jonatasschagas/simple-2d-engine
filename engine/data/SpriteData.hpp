#pragma once
#ifndef SPRITEDATA_HPP
#define SPRITEDATA_HPP

#include <string>

using namespace std;

class SpriteData
{
public:

    SpriteData(const string& name, int x, int y, int width, int height);

    string getName() const;
    int getX() const;
    int getY() const;
    int getWidth() const;
    int getHeight() const;

private:

    string m_name;
    int m_x;
    int m_y;
    int m_width;
    int m_height;

    void initializeMembers()
    {
        m_name = "";
        m_x = -1;
        m_y = -1;
        m_width = -1;
        m_height = -1;
    }

};


#endif //SPRITEDATA_HPP
