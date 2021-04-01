
#include "device.hpp"

/*void highlightKey(CorsairLedId ledId)
{
	for (auto x = .0; x < 2; x += .1) {
		auto val = static_cast<int>((1 - std::abs(x - 1)) * 255);
		auto ledColor = CorsairLedColor{ ledId, val, val, val };
		CorsairSetLedsColors(1, &ledColor);
		std::this_thread::sleep_for(std::chrono::milliseconds(30));
	}
}*/

int main()
{
	std::cout << "start" << std::endl;
	Device device(24);
	while(!device.isInitialized())
	{
		device.reInit();
	}
	EffectClear clear;
	EffectFade fade(0.9f);
	EffectBall ball;
	EffectRandom random;
	EffectStatic e_static(Color{0, 255, 0});
	RE_Swipe re_swipe(Color{255, 255, 255});
	device.addEffect(&fade);
	device.addReactiveEffect(&re_swipe);
	device.start();

	MSG msg;
    BOOL bRet;
    while(true)
    {
        bRet = GetMessage(&msg, NULL, 0, 0);

        if(bRet > 0)  // (bRet > 0 indicates a message that must be processed.)
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else if(bRet < 0)  // (bRet == -1 indicates an error.)
        {
            // Handle or log the error; possibly exit.
            // ...
        }
        else  // (bRet == 0 indicates "exit program".)
        {
            break;
        }
    }
	return msg.wParam;
}