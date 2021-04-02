
#ifndef HELPERS_HPP
#define HELPERS_HPP

#include <inttypes.h>
#include <random>
#include <math.h>
#include <utility>
#include <cstring>
#include <iostream>
#include <CUESDK.h>

#define MAX_X 450
#define MAX_Y 160
struct Color {
    int r;
    int g;
    int b;
};

enum Dir {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

struct Pos {
    int x;
    int y;
};

inline void setColor(CorsairLedColor& color, Color& newColor);          // change color easily
inline unsigned int scanCodeToCorsairLedIndex(unsigned int scanCode);   // handle converting keycodes to led ids

#endif
