#pragma once
#ifndef ResourceManager_hpp
#define ResourceManager_hpp

#include "Shader.hpp"
#include "Texture2D.hpp"
#include <glad/glad.h>
#include <map>
#include <memory>
#include <mutex>
#include <string>

using namespace std;

class ResourceManagerDestroyer;

class ResourceManager {
 public:
  /**
   * ResourceManager should not be cloneable.
   */
  ResourceManager(ResourceManager& other) = delete;

  /**
   * ResourceManager should not be assignable.
   */
  void operator=(ResourceManager const&) = delete;

  static ResourceManager* getInstance();

  Shader& loadShader(string const& vertexShaderFile,
                     string const& fragShaderFile, string const& name);

  Shader& getShader(string const& name);

  Texture2D& loadTexture(string const& file, string const& name);

  Texture2D& getTexture(string const& name);

 protected:
  virtual ~ResourceManager();
  friend class ResourceManagerDestroyer;

 private:
  ResourceManager();

  static ResourceManager* sm_pInstance;
  static ResourceManagerDestroyer sm_destroyer;
  static mutex sm_mutexInstance;

  map<string, unique_ptr<Shader>> m_shadersMap;
  map<string, unique_ptr<Texture2D>> m_texturesMap;

  void initializeMembers() {
    m_shadersMap.clear();
    m_texturesMap.clear();
  }
};

class ResourceManagerDestroyer {
 public:
  ResourceManagerDestroyer(ResourceManager* = 0);
  ~ResourceManagerDestroyer();
  void setSingleton(ResourceManager* pResourceManager);

 private:
  ResourceManager* m_pResourceManager;
};

#endif /* ResourceManager_hpp */