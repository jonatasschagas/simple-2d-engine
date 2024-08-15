#pragma once
#ifndef FileUtils_h
#define FileUtils_h

#include <fstream>
#include <sstream>
#include <streambuf>
#include <vector>

using namespace std;

inline string loadFile(string fileName) {
  ifstream t(fileName);
  string fileContents((istreambuf_iterator<char>(t)),
                      istreambuf_iterator<char>());
  return fileContents;
}

inline string findPathFromFile(string const& fileName) {
  size_t found;
  found = fileName.find_last_of("/\\");
  return fileName.substr(0, found);
}

#ifdef __APPLE__
#include <TargetConditionals.h>
#endif

#if TARGET_OS_OSX

inline vector<string> readLinesFromFile(string fileName) {
  ifstream infile(fileName);
  vector<string> lines;
  string line;

  while (getline(infile, line)) {
    lines.push_back(line);
  }

  return lines;
}

#elif TARGET_OS_IPHONE
// OBJ C implementation (.mm files)
string loadJSONString(string fileName);
vector<string> readLinesFromFile(string fileName, string fileType);
#endif

inline void writeToFile(string fileName, vector<string> const& lines) {
  fstream file;
  file.open(fileName, ios::out | ios::in | ios::app);
  for (unsigned long i = 0; i < lines.size(); i++) {
    file << lines[i] << endl;
  }
  file.close();
}

inline void writeToFile(string fileName, string const& contents,
                        bool overwrite = false) {
  fstream file;
  file.open(fileName, ios::out | ios::in | (overwrite ? ios::trunc : ios::app));
  file << contents << endl;
  file.close();
}

#endif /* FileUtils_h */
