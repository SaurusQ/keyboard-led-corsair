
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

class EffectFade : public Effect
{
    public:
        EffectFade(float fcr, float fcg, float fcb)
            : Effect(), fcr_(fcr), fcg_(fcg), fcb_(fcb) {
            if(fcr_ < 0.0f || fcr_ > 1.0f
                || fcg_ < 0.0f || fcg_ > 1.0f
                || fcb_ < 0.0f || fcb_ > 1.0f)
                throw "Wrong coef";
        }
        EffectFade(float fadeCoef)
            : Effect(), fcr_(fadeCoef), fcg_(fadeCoef), fcb_(fadeCoef)
        {
            if(fadeCoef < 0.0f || fadeCoef > 1.0f) throw "Wrong coef";    
        }
        virtual ~EffectFade() {}
        virtual void run(CorsairLedPosition* pPos, CorsairLedColor* pCol, size_t len);
    protected:
        float fcr_;
        float fcg_;
        float fcb_;
};
class EffectBall : public Effect
{
    public:
        EffectBall();
        virtual ~EffectBall() {}
        virtual void run(CorsairLedPosition* pPos, CorsairLedColor* pCol, size_t len);
    protected:
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
};

class EffectWave : public Effect
{
    public:
        EffectWave() : Effect() {}
        virtual ~EffectWave() {}
        virtual void run(CorsairLedPosition* pPos, CorsairLedColor* pCol, size_t len);
};

class EffectStatic : public Effect
{
    public:
        EffectStatic() : Effect() {}
        virtual ~EffectStatic() {}
        virtual void run(CorsairLedPosition* pPos, CorsairLedColor* pCol, size_t len);
    protected:
        Color color_ = {0, 255, 0};
};

#endif
