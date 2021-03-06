
#ifndef REACTIVE_EFFECT_HPP
#define REACTIVE_EFFECT_HPP

#include "effect.hpp"
#include "helpers.hpp"

class ReactiveEffect : public Effect
{
    public:
        ReactiveEffect() : Effect() {}
        virtual ~ReactiveEffect() {}
        virtual bool onlyReactive() { return true; }
        virtual bool isReactive() { return true; }
        virtual void keyEvent(unsigned int ledIdx, bool keyDown,
            CorsairLedPosition* pPos, CorsairLedColor* pCol, size_t len) = 0;
};

class RE_Swipe : public ReactiveEffect
{
    public:
        RE_Swipe(Color color) : ReactiveEffect(), color_(color) {}
        virtual ~RE_Swipe() {}
        virtual bool onlyReactive() { return false; }
        virtual void run(CorsairLedPosition* pPos, CorsairLedColor* pCol, size_t len);
        virtual void keyEvent(unsigned int ledIdx, bool keyDown,
            CorsairLedPosition* pPos, CorsairLedColor* pCol, size_t len);
    protected:
        Color color_;
        double horizontalPos_ = 0.0f;
        int maxX = 450;
        int maxY = 160;
};

class RE_Snake : public ReactiveEffect
{
    public:
        RE_Snake(Color snakeColor, Color fruitColor, float speed, float stepSize);
        virtual ~RE_Snake() {}
        virtual bool onlyReactive() { return false; }
        virtual void run(CorsairLedPosition* pPos, CorsairLedColor* pCol, size_t len);
        virtual void keyEvent(unsigned int ledIdx, bool keyDown,
            CorsairLedPosition* pPos, CorsairLedColor* pCol, size_t len);
    protected:
        Color colorSnake_;
        Color colorFruit_;
        int speed_;                                 // how many frames does it take for the snake to move one block
        float stepSize_;
        std::vector<Pos> snakeBody_;
        Pos fruit_;
        Dir dir_ = Dir::UP;
        int maxX = 450;
        int maxY = 160;
};

class RE_Key : public ReactiveEffect
{
    public:
        RE_Key(Color color) : ReactiveEffect(), color_(color) {}
        virtual ~RE_Key() {}
        virtual bool onlyReactive() { return true; }
        virtual void run(CorsairLedPosition* pPos, CorsairLedColor* pCol, size_t len) {}
        virtual void keyEvent(unsigned int ledIdx, bool keyDown,
            CorsairLedPosition* pPos, CorsairLedColor* pCol, size_t len);
    protected:
        Color color_;

};


#endif
