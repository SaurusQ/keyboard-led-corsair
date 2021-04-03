
#include "helpers.hpp"

bool isInSquare(Pos midPoint, float size, Pos another)
{
    return std::abs(midPoint.x - another.x) <= size
        && std::abs(midPoint.y - another.y) <= size;
}

bool isInCircle(Pos midPoint, float size, Pos another)
{
    return size >= std::sqrt(std::pow(midPoint.x - another.x, 2) + std::pow(midPoint.y - another.y, 2));
}

void setColor(CorsairLedColor& color, Color& newColor)
{
    std::memcpy(&color.r, &newColor, sizeof(Color));
}

unsigned int scanCodeToCorsairLedIndex(unsigned int scanCode)
{
    switch (scanCode)
    {
        case 0x01: // ESC
            return 93;
        case 0x02: // 1
            return 106;
        case 0x03: // 2
            return 107;
        case 0x04: // 3
            return 108;
        case 0x05: // 4
            return 109;
        case 0x06: // 5
            return 110;
        case 0x07: // 6
            return 111;
        case 0x08: // 7
            return 112;
        case 0x09: // 8
            return 113;
        case 0x0A: // 9
            return 0;
        case 0x0B: // 0
            return 1;
        case 0x0C: // +
            return 2;
        case 0x0D: // ´
            return 49;
        case 0x0E: // BKSP
            return 50;
        case 0x0F: // Tab
            return 3;
        case 0x10: // Q
            return 4;
        case 0x11: // W
            return 5;
        case 0x12: // E
            return 6;
        case 0x13: // R
            return 7;
        case 0x14: // T
            return 8;
        case 0x15: // Y
            return 9;
        case 0x16: // U
            return 59;
        case 0x17: // I
            return 60;
        case 0x18: // O
            return 61;
        case 0x19: // P
            return 62;
        case 0x1A: // Å
            return 63;
        case 0x1B: // ^^
            return 46;
        case 0x1C: // Enter also numpad enter
            return 22; // 48
        case 0x1D: // Ctrl
            return 90; // 55 RIGHT
        case 0x1E: // A
            return 65;
        case 0x1F: // S
            return 66;
        case 0x20: // D
            return 67;
        case 0x21: // F
            return 68;
        case 0x22: // G
            return 69;
        case 0x23: // H
            return 70;
        case 0x24: // J
            return 71;
        case 0x25: // K
            return 72;
        case 0x26: // L
            return 73;
        case 0x27: // Ö
            return 74;
        case 0x28: // Ä
            return 75;
        case 0x29: // §
            return 105;
        case 0x2A: // Left shift
            return 76;
        case 0x2B: // *
            return 47;
        case 0x2C: // Z
            return 78;
        case 0x2D: // X
            return 79;
        case 0x2E: // C
            return 80;
        case 0x2F: // V
            return 82;
        case 0x30: // B
            return 84;
        case 0x31: // N
            return 85;
        case 0x32: // M
            return 86;
        case 0x33: // ,
            return 87;
        case 0x34: // .
            return 88;
        case 0x35: // num * and -_
            return 18; // 89
        case 0x36: // Right shift
            return 54;
        case 0x37: // num / and pause break
            return 19;
        case 0x39: // space
            return 34;
        case 0x3A: // CpsLk
            return 64;
        case 0x3B: // F1
            return 94;
        case 0x3C: // F2
            return 95;
        case 0x3D: // F3
            return 96;
        case 0x3E: // F4
            return 97;
        case 0x3F: // F5
            return 98;
        case 0x40: // F6
            return 99;
        case 0x41: // F7
            return 100;
        case 0x42: // F8
            return 101;
        case 0x43: // F9
            return 102;
        case 0x44: // F10
            return 103;
        case 0x45: // Num Lk
            return 17;
        case 0x46: // print screen
            return 41;
        case 0x47: // num 7 Home
            return 23;
        case 0x48: // num 8 Up Arrow
            return 24;
        case 0x49: // num 9 Pg Up
            return 25;
        case 0x4A: // num -
            return 20;
        case 0x4B: // num 4 left arrow
            return 26;
        case 0x4C: // num 5
            return 27;
        case 0x4D: // num 6 right arrow
            return 28;
        case 0x4E: // num +
            return 21;
        case 0x4F: // num 1 End
            return 29;
        case 0x50: // num 2 Dn Arrow
            return 30;
        case 0x51: // num 3 Pg Dn
            return 31;
        case 0x52: // num 0 Ins
            return 32;
        case 0x53: // num Del .
            return 33;
        case 0x54: // SH F1
            return 36;
        case 0x55: // SH F2
            return 12;
        case 0x56: // SH F3
            return 77;
        case 0x57: // F11
            return 104;
        case 0x58: // F12
            return 39;
        case 0x59: // SH F6
            return 0;
        case 0x5A: // SH F7
            return 0;
        case 0x5B: // left windows
            return 91;
        case 0x5C: // right windows
            return 36;
        case 0x5D: // right menu
            return 37;
        default:
            return 0;
    }
}
