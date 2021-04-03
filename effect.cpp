
#include "effect.hpp"
#include <iostream>

std::random_device rd;
std::mt19937 rng(rd());
std::uniform_int_distribution<int> distr_color(0, 255);
std::uniform_real_distribution<float> ditr_sided(-1.0f, 1.0f);

unsigned int Effect::fps_ = 0;

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

E_Ball::E_Ball(Color color, int radius, float speed)
    : Effect(),
    color_(color),
    radius_(radius),
    speed_(speed)
{
    std::uniform_int_distribution<int> uidX(0.0f, MAX_X);
    std::uniform_int_distribution<int> uidY(0.0f, MAX_Y);
    //posX = (float)uidX(rng_eff);
    //posY = (float)uidY(rng_eff);
    pos_ = Pos{100.0f, 100.0f};
}

void E_Ball::run(CorsairLedPosition* pPos, CorsairLedColor* pCol, size_t len)
{
    pos_.x += dirVector.first;
    pos_.y += dirVector.second;
    if((pos_.x < radius_ && dirVector.first < 0.0f)
        || (pos_.x > MAX_X - radius_ && dirVector.first > 0.0f))
    {
        float random = ditr_sided(rng) * 1.0f;
        dirVector.first = -dirVector.first + random;
        dirVector.second -= random;
    }
    else if((pos_.y < radius_ && dirVector.second < 0.0f) 
        || (pos_.y > MAX_Y - radius_ && dirVector.second > 0.0f))
    {
        float random = ditr_sided(rng) * 1.0f;
        dirVector.second = -dirVector.second + random;
        dirVector.first -= random;
    }
    for(int i = 0; i < len; i++)
    {
        if(isInCircle(pos_, radius_, Pos{(float)pPos[i].left, (float)pPos[i].top}))
        {
            setColor(pCol[i], color_);
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
