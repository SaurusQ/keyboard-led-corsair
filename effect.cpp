
#include "effect.hpp"
#include <iostream>

std::random_device rd;
std::mt19937 rng(rd());
std::uniform_int_distribution<int> distr_color(0, 255);

unsigned int Effect::fps_ = 0;

E_Ball::E_Ball() : Effect() 
{
    std::uniform_int_distribution<int> uidX(0.0f, MAX_X);
    std::uniform_int_distribution<int> uidY(0.0f, MAX_Y);
    //posX = (float)uidX(rng_eff);
    //posY = (float)uidY(rng_eff);
    posX = 100;
    posY = 100;
}

void E_Clear::run(CorsairLedPosition* pPos, CorsairLedColor* pCol, size_t len)
{
    for(int i = 0; i < len; i++)
    {
        std::memset(&pCol[i].r, 0, sizeof(int) * 3);
    }
}

void E_Fade::run(CorsairLedPosition* pPos, CorsairLedColor* pCol, size_t len)
{
    for(int i = 0; i < len; i++)
    {
        pCol[i].r -= pCol[i].r * fcr_ / fps_;
        pCol[i].g -= pCol[i].g * fcr_ / fps_;
        pCol[i].b -= pCol[i].b * fcr_ / fps_;
    }
}

void E_Ball::run(CorsairLedPosition* pPos, CorsairLedColor* pCol, size_t len)
{
    int diff;
    posX += dirVector.first;
    posY += dirVector.second;
    if((posX < radius && dirVector.first < 0)
        || (posX > MAX_X - radius && dirVector.first > 0))
    {
        dirVector.first = -dirVector.first;
    }
    else if((posY < radius && dirVector.second < 0) 
        || (posY > MAX_Y - radius && dirVector.second > 0))
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

void E_Random::run(CorsairLedPosition* pPos, CorsairLedColor* pCol, size_t len)
{
    if(!crazy_)
    {
        std::uniform_int_distribution<int> distr_array(0, len - 1);
        storage_ += frequency_;
        while(storage_ > 1.0f)
        {
            storage_ -= 1.0f;
            Color c = {distr_color(rng), distr_color(rng), distr_color(rng)};
            setColor(pCol[distr_array(rng)], c);
        }
    }
    else
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
}

void E_Wave::run(CorsairLedPosition* pPos, CorsairLedColor* pCol, size_t len)
{

}

void E_Static::run(CorsairLedPosition* pPos, CorsairLedColor* pCol, size_t len)
{
    for(int i = 0; i < len; i++)
    {
        setColor(pCol[i], color_);
    }
}

void E_OneByOne::run(CorsairLedPosition* pPos, CorsairLedColor* pCol, size_t len)
{
    static int a = 0;
    if(a < 20) 
    {
        a++;
        return;
    }
    a = 0;
    std::cout << std::dec << idx << std::endl;
    if(idx >= len) idx = 0;
    setColor(pCol[idx], color_);
    idx++;
}
