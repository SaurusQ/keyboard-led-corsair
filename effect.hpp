
#ifndef EFFECT_HPP
#define EFFECT_HPP

#include <inttypes.h>
#include <random>
#include <math.h>
#include <utility>
#include <cstring>

#include <CUESDK.h>

struct Color {
    int r;
    int g;
    int b;
};

class Effect
{
    public:
        Effect() {}
        virtual ~Effect() {}
        virtual void run(CorsairLedPosition* pPos, CorsairLedColor* pCol, size_t len) = 0;
    protected:
        int alpha; //TODO
};

class EffectClear : public Effect
{
    public:
        EffectClear() : Effect() {}
        virtual ~EffectClear() {}
        virtual void run(CorsairLedPosition* pPos, CorsairLedColor* pCol, size_t len);
};

class EffectBall : public Effect
{
    public:
        EffectBall();
        virtual ~EffectBall() {}
        virtual void run(CorsairLedPosition* pPos, CorsairLedColor* pCol, size_t len);
    private:
        int posX;
        int posY;
        int maxX = 450;
        int maxY = 160;
        int radius = 30;
        std::pair<int, int> dirVector = {10, 10};
};

class EffectRandom : public Effect
{
    public:
        EffectRandom() : Effect() {}
        virtual ~EffectRandom() {}
        virtual void run(CorsairLedPosition* pPos, CorsairLedColor* pCol, size_t len);
    private:
};

class EffectWave : public Effect
{
    public:
        EffectWave() : Effect() {}
        virtual ~EffectWave() {}
        virtual void run(CorsairLedPosition* pPos, CorsairLedColor* pCol, size_t len);
    private:
};

class EffectStatic : public Effect
{
    public:
        EffectStatic() : Effect() {}
        virtual ~EffectStatic() {}
        virtual void run(CorsairLedPosition* pPos, CorsairLedColor* pCol, size_t len);
    private:
        Color color_ = {0, 255, 0};
};

#endif
