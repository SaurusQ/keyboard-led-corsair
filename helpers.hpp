
#ifndef HELPERS_HPP
#define HELPERS_HPP

#include <inttypes.h>
#include <random>
#include <math.h>
#include <utility>
#include <cstring>
#include <iostream>
#include <CUESDK.h>

#define MAX_X 430 // was 460
#define MAX_Y 130 // was 150
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
    float x;
    float y;
};

bool isInSquare(Pos midPoint, float size, Pos another);
void setColor(CorsairLedColor& color, Color& newColor);          // change color easily
unsigned int scanCodeToCorsairLedIndex(unsigned int scanCode);   // handle converting keycodes to led ids

#endif
