
#include "effect.hpp"
#include <iostream>

std::random_device rd;
std::mt19937 rng(rd());
std::uniform_int_distribution<int> distr_color(0, 255);

EffectBall::EffectBall() : Effect() 
{
    std::uniform_int_distribution<int> uidX(0.0f, maxX);
    std::uniform_int_distribution<int> uidY(0.0f, maxY);
    //posX = (float)uidX(rng_eff);
    //posY = (float)uidY(rng_eff);
    posX = 100;
    posY = 100;
}

void EffectClear::run(CorsairLedPosition* pPos, CorsairLedColor* pCol, size_t len)
{
    for(int i = 0; i < len; i++)
    {
        std::memset(&pCol[i].r, 0, sizeof(int) * 3);
    }
}

void EffectFade::run(CorsairLedPosition* pPos, CorsairLedColor* pCol, size_t len)
{
    for(int i = 0; i < len; i++)
    {
        pCol[i].r *= fcr_;
        pCol[i].g *= fcg_;
        pCol[i].b *= fcb_;;
    }
}

void EffectBall::run(CorsairLedPosition* pPos, CorsairLedColor* pCol, size_t len)
{
    int diff;
    posX += dirVector.first;
    posY += dirVector.second;
    if((posX < radius && dirVector.first < 0)
        || (posX > maxX - radius && dirVector.first > 0))
    {
        dirVector.first = -dirVector.first;
    }
    else if((posY < radius && dirVector.second < 0) 
        || (posY > maxY - radius && dirVector.second > 0))
    {
        dirVector.second = -dirVector.second;
    }
    for(int i = 0; i < len; i++)
    {
        diff = std::sqrt(std::pow(posX - pPos[i].left, 2) + std::pow(posY - pPos[i].top, 2));
        if(diff <= radius)
        {
            pCol[i].r = 255; //std::abs((int)((diff - radius) * (255.0f / radius)));
        }
    }
}

void EffectRandom::run(CorsairLedPosition* pPos, CorsairLedColor* pCol, size_t len)
{
    for(int i = 0; i < len; i++)
    {
        //pCol[i].r = distr_color(rng);
        //pCol[i].g = distr_color(rng);
        //pCol[i].b = distr_color(rng);
        pCol[i].r = 0;
        pCol[i].g = 0;
        pCol[i].b = 0;
        switch(distr_color(rng) % 3)
        {
            case 0:
                pCol[i].r = 255;
                break;
            case 1:
                pCol[i].g = 255;
                break;
            case 2:
                pCol[i].b = 255;
                break;
        }
    }    
}

void EffectWave::run(CorsairLedPosition* pPos, CorsairLedColor* pCol, size_t len)
{

}

void EffectStatic::run(CorsairLedPosition* pPos, CorsairLedColor* pCol, size_t len)
{
    for(int i = 0; i < len; i++)
    {
        std::memcpy(&pCol[i].r, &color_, sizeof(color_));
    }
}

void RE_Swipe::run(CorsairLedPosition* pPos, CorsairLedColor* pCol, size_t len)
{
    for(int i = 0; i < len; i++)
    {
        if(pPos[i].left < horizontalPos_) 
            std::memcpy(&pCol[i].r, &color_, sizeof(color_));
    }
}

void RE_Swipe::keyEvent(int keyIdx, bool keyDown,
    CorsairLedPosition* pPos, CorsairLedColor* pCol, size_t len)

{
    if(keyDown) horizontalPos_ += 10.0f;
    if(horizontalPos_ > maxX) horizontalPos_ = 0.0f;
}
