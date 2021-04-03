
#ifndef EFFECT_HPP
#define EFFECT_HPP

#include <inttypes.h>
#include <random>
#include <math.h>
#include <utility>
#include <cstring>
#include <iostream>

#include <CUESDK.h>
#include "helpers.hpp"

// globals
extern std::random_device rd;
extern std::mt19937 rng;

class Effect
{
    public:
        Effect() {}
        virtual ~Effect() {}
        virtual void run(CorsairLedPosition* pPos, CorsairLedColor* pCol, size_t len) = 0;
        static void setFps(unsigned int fps) { fps_ = fps; }
    protected:
        int alpha; //TODO
        static unsigned int fps_;
};

class E_Clear : public Effect
{
    public:
        E_Clear() : Effect() {}
        virtual ~E_Clear() {}
        virtual void run(CorsairLedPosition* pPos, CorsairLedColor* pCol, size_t len);
};

class E_Fade : public Effect
{
    public:
        E_Fade(float fcr, float fcg, float fcb)
            : Effect(), fcr_(fcr), fcg_(fcg), fcb_(fcb) {
            if(fcr_ < 0.0f || fcr_ > 1.0f
                || fcg_ < 0.0f || fcg_ > 1.0f
                || fcb_ < 0.0f || fcb_ > 1.0f)
                throw "Wrong coef";
        }
        E_Fade(float fadeCoef)
            : Effect(), fcr_(fadeCoef), fcg_(fadeCoef), fcb_(fadeCoef)
        {
            if(fadeCoef < 0.0f || fadeCoef > 1.0f) throw "Wrong coef";    
        }
        virtual ~E_Fade() {}
        virtual void run(CorsairLedPosition* pPos, CorsairLedColor* pCol, size_t len);
    protected:
        float fcr_;
        float fcg_;
        float fcb_;
};
class E_Ball : public Effect
{
    public:
        E_Ball(Color color, int radius, float speed);
        virtual ~E_Ball() {}
        virtual void run(CorsairLedPosition* pPos, CorsairLedColor* pCol, size_t len);
    protected:
        Pos pos_;
        int radius_ ;
        float speed_;
        Color color_;
        std::pair<float, float> dirVector = {10, 10};
};

class E_Random : public Effect
{
    public:
        E_Random(float frequency, bool crazy = false) : Effect(), frequency_(frequency), crazy_(crazy_) {}
        virtual ~E_Random() {}
        virtual void run(CorsairLedPosition* pPos, CorsairLedColor* pCol, size_t len);
    protected:
        float frequency_; // how many random colors per frame
        float storage_ = 0.0f;
        bool crazy_;

};

class E_Wave : public Effect
{
    public:
        E_Wave() : Effect() {}
        virtual ~E_Wave() {}
        virtual void run(CorsairLedPosition* pPos, CorsairLedColor* pCol, size_t len);
};

class E_Static : public Effect
{
    public:
        E_Static(Color color) 
            : Effect(), color_(color) {}
        virtual ~E_Static() {}
        virtual void run(CorsairLedPosition* pPos, CorsairLedColor* pCol, size_t len);
    protected:
        Color color_;
};

class E_OneByOne : public Effect
{
    public:
        E_OneByOne(Color color) : Effect(), color_(color) {}
        virtual ~E_OneByOne() {}
        virtual void run(CorsairLedPosition* pPos, CorsairLedColor* pCol, size_t len);
    protected:
        Color color_;
        unsigned int idx = 0;
};

#endif
