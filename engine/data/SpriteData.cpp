#include "SpriteData.hpp"

using namespace std;

SpriteData::SpriteData(string const& name, int x, int y, int width,
                       int height) {
  initializeMembers();

  m_name = name;
  m_x = x;
  m_y = y;
  m_width = width;
  m_height = height;
}

string const& SpriteData::getName() const { return m_name; }

int SpriteData::getX() const { return m_x; }

int SpriteData::getY() const { return m_y; }

int SpriteData::getWidth() const { return m_width; }

int SpriteData::getHeight() const { return m_height; }
