
#include "reactiveEffect.hpp"

std::random_device rd;
std::mt19937 rng(rd());
std::uniform_int_distribution<float> fruit_x(0.0f, MAX_X);
std::uniform_int_distribution<float> fruit_y(0.0f, MAX_Y);

void RE_Swipe::run(CorsairLedPosition* pPos, CorsairLedColor* pCol, size_t len)
{
    for(int i = 0; i < len; i++)
    {
        if(pPos[i].left < horizontalPos_ && pPos[i].left > horizontalPos_ - 30.0f) 
            std::memcpy(&pCol[i].r, &color_, sizeof(color_));
    }
}

void RE_Swipe::keyEvent(unsigned int ledIdx, bool keyDown,
    CorsairLedPosition* pPos, CorsairLedColor* pCol, size_t len)

{
    if(keyDown) horizontalPos_ += 10.0f;
    if(horizontalPos_ > maxX) horizontalPos_ = 0.0f;
}

RE_Snake::RE_Snake(Color snakeColor, Color fruitColor, float speed)
    : ReactiveEffect(),
    colorSnake_(snakeColor),
    colorFruit_(fruitColor)
{
    snakeBody_.push_back(Pos{0, 0});
    fruit_ = Pos{fruit_x(rng), fruit_y(rng)};
    speed_ = speed / fps_;
}

void RE_Snake::run(CorsairLedPosition* pPos, CorsairLedColor* pCol, size_t len)
{
    constexpr float close = 10.0f;
    for(int i = 0; i < len; i++)
    {
        
    }
    static unsigned int track = 0;
    if(track < speed_)
    {
        track++;
        return;
    }
    track = 0;


}

void RE_Snake::keyEvent(unsigned int ledIdx, bool keyDown,
    CorsairLedPosition* pPos, CorsairLedColor* pCol, size_t len)
{
    if(ledIdx == 26) dir_ = Dir::LEFT;
    else if(ledIdx == 28) dir_ = Dir::RIGHT;
    else if(ledIdx == 30) dir_ = Dir::DOWN;
    else if(ledIdx == 24) dir_ = Dir::UP;
}

void RE_Key::keyEvent(unsigned int ledIdx, bool keyDown,
    CorsairLedPosition* pPos, CorsairLedColor* pCol, size_t len)
{
    std::memcpy(&pCol[ledIdx].r, &color_, sizeof(color_));
}
