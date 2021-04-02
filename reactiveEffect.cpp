
#include "reactiveEffect.hpp"

std::uniform_int_distribution<int> fruit_x(0.0f, MAX_X);
std::uniform_int_distribution<int> fruit_y(0.0f, MAX_Y);

void RE_Swipe::run(CorsairLedPosition* pPos, CorsairLedColor* pCol, size_t len)
{
    for(int i = 0; i < len; i++)
    {
        if(pPos[i].left < horizontalPos_ && pPos[i].left > horizontalPos_ - 30.0f)
            setColor(pCol[i], color_);
    }
}

void RE_Swipe::keyEvent(unsigned int ledIdx, bool keyDown,
    CorsairLedPosition* pPos, CorsairLedColor* pCol, size_t len)

{
    if(keyDown) horizontalPos_ += 10.0f;
    if(horizontalPos_ > maxX) horizontalPos_ = 0.0f;
}

RE_Snake::RE_Snake(Color snakeColor, Color fruitColor, float speed, float stepSize)
    : ReactiveEffect(),
    colorSnake_(snakeColor),
    colorFruit_(fruitColor),
    stepSize_(stepSize)
{
    snakeBody_.push_back(Pos{100.0f, 100.0f});
    fruit_ = Pos{(float)fruit_x(rng), (float)fruit_y(rng)};
    speed_ = speed * fps_;
}

void RE_Snake::run(CorsairLedPosition* pPos, CorsairLedColor* pCol, size_t len)
{
    static bool eat = false;
    // eating
    if(isInSquare(snakeBody_[0], stepSize_, fruit_))
    {
        fruit_ = Pos{(float)fruit_x(rng), (float)fruit_y(rng)};
        eat = true;
    }

    // rendering
    for(int i = 0; i < len; i++)
    {
        Pos pos = {(float)pPos[i].left, (float)pPos[i].top};
        if(isInSquare(fruit_, stepSize_, pos))
            setColor(pCol[i], colorFruit_);
        else
        {
            for(auto& b : snakeBody_)
            {
                if(isInSquare(b, stepSize_, pos))
                {
                    setColor(pCol[i], colorSnake_);
                    break;
                }
            }
        }
    }

    // slower logic updates
    static unsigned int track = 0;
    if(track < speed_)
    {
        track++;
        return;
    }
    track = 0;

    // logic
    Pos newPos = snakeBody_[0];
    if(dir_ == Dir::DOWN) newPos.y += stepSize_;
    else if(dir_ == Dir::UP) newPos.y -= stepSize_;
    else if(dir_ == Dir::LEFT) newPos.x -= stepSize_;
    else if(dir_ == Dir::RIGHT) newPos.x += stepSize_;
    Pos temp;
    for(auto& pos : snakeBody_)
    {
        temp = pos;
        pos = newPos;
        newPos = temp;
    }
    if(eat) snakeBody_.push_back(newPos);

    eat = false;
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
    setColor(pCol[ledIdx], color_);
}
