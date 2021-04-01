
#ifndef DEVICE_HPP
#define DEVICE_HPP

#include <CUESDK.h>

#include <string>
#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>
#include <vector>
#include <windows.h>

#include "effect.hpp"

class Device // TODO singleton
{
    public:
        Device(unsigned int fps);                       // fps in which the effects are rendered, start to connection to the keyboard with reInit()
        ~Device();                                      // release control of the keyboard
        bool reInit();                                  // handshake to the keyboard and fetch information of the keyboard layout
        void start();                                   // start the lighting thread
        void stop();                                    // stop the ligthing thread
        void run();                                     // run one frame from the effects
        void addEffect(Effect* pEff);                   // add effect to be rendered
        CorsairLedColor* posToColor(
            CorsairLedPosition* pPos, size_t len);      // get the color of each key position
        bool isInitialized() { return initialized_; }   // has the reInit completed successfully
        std::string errToString(CorsairError err);      // convert from corsair error message to string
    private:
        void setKeypressHook();                         // hooks the program to deted system wide keypresses from windows
        unsigned int fps_;                              // fps of the effects
        std::thread lightingThread_;                    // thread that handles ligthing
        std::atomic<bool> lightingThreadRunning_;       // is the ligthing thread running
        bool initialized_ = false;                      // is the device initialized 
        CorsairLedPosition* pPositions_;                // list of all keys on keyboard with their positions
        CorsairLedColor* pColors_;                      // list of all ledIds and their colors, initialized from pPositions_
        size_t numKeys_;                                // number of keys, size of pPostions_ and pColors_
        std::vector<Effect*> pEffects_;                 // effects currently in use, rendered in order from first to last
    
        static Device* pInstance_;
        static HHOOK hook_;                             // hook for the current low level keyboard hook
        static LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
};

#endif
