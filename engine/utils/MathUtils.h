#pragma once
#pragma clang diagnostic ignored "-Wunsequenced"
#ifndef MathUtils_h
#define MathUtils_h

#include "glm/glm.hpp"
#include <iostream>
#include <random>

inline float simple_lerp(float point1, float point2, float alpha) {
  return point1 + alpha * (point2 - point1);
}

inline float bounceEaseOut(float t, float b, float c, float d) {
  if ((t /= d) < (1 / 2.75f)) {
    return c * (7.5625f * t * t) + b;
  } else if (t < (2 / 2.75f)) {
    float postFix = t -= (1.5f / 2.75f);
    return c * (7.5625f * (postFix)*t + .75f) + b;
  } else if (t < (2.5 / 2.75)) {
    float postFix = t -= (2.25f / 2.75f);
    return c * (7.5625f * (postFix)*t + .9375f) + b;
  } else {
    float postFix = t -= (2.625f / 2.75f);
    return c * (7.5625f * (postFix)*t + .984375f) + b;
  }
}

inline float bounceEaseIn(float t, float b, float c, float d) {
  return c - bounceEaseOut(d - t, 0, c, d) + b;
}

inline float bounceEaseInOut(float t, float b, float c, float d) {
  if (t < d / 2)
    return bounceEaseIn(t * 2, 0, c, d) * .5f + b;
  else
    return bounceEaseOut(t * 2 - d, 0, c, d) * .5f + c * .5f + b;
}

inline float cubicEaseIn(float t, float b, float c, float d) {
  return c * (t /= d) * t * t + b;
}

inline float cubicEaseOut(float t, float b, float c, float d) {
  return c * ((t = t / d - 1) * t * t + 1) + b;
}

inline float cubicEaseInOut(float t, float b, float c, float d) {
  if ((t /= d / 2) < 1) return c / 2 * t * t * t + b;
  return c / 2 * ((t -= 2) * t * t + 2) + b;
}

inline float getRandomFloat(float lower, float upper) {
  std::random_device rd;
  std::mt19937 e2(rd());
  std::uniform_real_distribution<float> dist(lower, upper);
  return dist(e2);
}

inline int getRandomInt(int lower, int upper) {
  std::random_device rd;
  std::mt19937 e2(rd());
  std::uniform_int_distribution<int> dist(lower, upper);
  return dist(e2);
}

inline bool checkCollision(float x1, float y1, float width1, float height1,
                           float x2, float y2, float width2, float height2) {
  bool collidesX =
      (x1 >= x2 && x1 <= (x2 + width2)) || (x2 >= x1 && x2 <= (x1 + width1));
  bool collidesY =
      (y1 >= y2 && y1 <= (y2 + height2)) || (y2 >= y1 && y2 <= (y1 + height1));
  return collidesX && collidesY;
}

inline float calculateDistanceBetweenNodes(float x1, float y1, float x2,
                                           float y2) {
  // distance between points -> pithagoras
  return sqrtf(pow(abs(x2 - x1), 2) + pow(abs(y2 - y1), 2));
}

inline float lerp(float point1, float point2, float alpha) {
  return point1 + alpha * (point2 - point1);
}

inline void printMatrix(glm::mat4 const& matrix) {
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      std::cout << matrix[i][j] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

inline double degreesToRadians(double degrees) {
  return degrees * M_PI / 180.0;
}

inline int16_t clipToRangeInteger16(int32_t value) {
  if (value > 32767) {
    return 32767;  // Clip to the maximum value
  } else if (value < -32768) {
    return -32768;  // Clip to the minimum value
  } else {
    return static_cast<int16_t>(value);  // Value is within the valid range
  }
}

#endif /* MathUtils_h */
