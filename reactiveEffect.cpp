
#include "reactiveEffect.hpp"

void RE_Swipe::run(CorsairLedPosition* pPos, CorsairLedColor* pCol, size_t len)
{
    for(int i = 0; i < len; i++)
    {
        if(pPos[i].left < horizontalPos_ && pPos[i].left > horizontalPos_ - 30.0f) 
            std::memcpy(&pCol[i].r, &color_, sizeof(color_));
    }
}

void RE_Swipe::keyEvent(int keyIdx, bool keyDown,
    CorsairLedPosition* pPos, CorsairLedColor* pCol, size_t len)

{
    if(keyDown) horizontalPos_ += 10.0f;
    if(horizontalPos_ > maxX) horizontalPos_ = 0.0f;
}

void RE_Snake::run(CorsairLedPosition* pPos, CorsairLedColor* pCol, size_t len)
{

}

void RE_Snake::keyEvent(int keyIdx, bool keyDown,
    CorsairLedPosition* pPos, CorsairLedColor* pCol, size_t len)
{
    std::cout << keyIdx << std::endl;
}