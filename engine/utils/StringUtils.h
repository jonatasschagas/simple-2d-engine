#ifndef StringUtils_h
#define StringUtils_h

#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <stdio.h>
#include <string>
#include <vector>

using std::string;
using std::stringstream;

inline size_t split(std::string const& txt, std::vector<std::string>& strs,
                    char ch) {
  size_t pos = txt.find(ch);
  size_t initialPos = 0;
  strs.clear();

  // Decompose statement
  while (pos != std::string::npos) {
    strs.push_back(txt.substr(initialPos, pos - initialPos));
    initialPos = pos + 1;

    pos = txt.find(ch, initialPos);
  }

  // Add the last one
  strs.push_back(
      txt.substr(initialPos, std::min(pos, txt.size()) - initialPos + 1));

  return strs.size();
}

inline int stringToInt(std::string const& s) {
  stringstream stream(s);
  int val = 0;
  stream >> val;
  return val;
}

inline string convertToString(char* a, int size) {
  int i;
  string s = "";
  for (i = 0; i < size; i++) {
    s = s + a[i];
  }
  return s;
}

template <typename... Args>
inline std::string stringFormat(std::string const& format, Args... args) {
  int size_s = std::snprintf(nullptr, 0, format.c_str(), args...) +
               1;  // Extra space for '\0'
  if (size_s <= 0) {
    throw std::runtime_error("Error during formatting.");
  }
  auto size = static_cast<size_t>(size_s);
  std::unique_ptr<char[]> buf(new char[size]);
  std::snprintf(buf.get(), size, format.c_str(), args...);
  return std::string(buf.get(),
                     buf.get() + size - 1);  // We don't want the '\0' inside
}

inline std::string bytesToHexString(char const* bytes, size_t length) {
  std::stringstream stream;
  for (size_t i = 0; i < length; ++i) {
    stream << std::hex << static_cast<int>(bytes[i]);
  }
  return stream.str();
}

#endif /* StringUtils_h */
