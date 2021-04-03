
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
	E_Clear e_clear;
	E_Fade e_fade(1.0f);

	E_Ball e_ball_r(Color{255, 0, 0}, 20.0f, 0.2f);
	E_Ball e_ball_g(Color{0, 255, 0}, 20.0f, 0.2f);
	E_Ball e_ball_b(Color{0, 0, 255}, 20.0f, 0.2f);
	E_Ball e_ball_pink(Color{255, 85, 255}, 20.0f, 0.2f);

	E_Random e_random(10.0f);
	E_OneByOne e_oneByOne(Color{255, 255, 255});
	E_Static e_static(Color{0, 255, 0});
	RE_Swipe re_swipe(Color{255, 255, 255});
	RE_Snake re_snake(Color{255, 255, 0}, Color{0, 255, 255}, 0.001f, 10.0f);
	RE_Key re_key(Color{0, 255, 0});
	
	device.addEffect(&e_fade);
	device.addEffect(&e_ball_r);
	device.addEffect(&e_ball_g);
	device.addEffect(&e_ball_b);
	device.addEffect(&e_ball_pink);

	//device.addEffect(&e_clear);
	//device.addReactiveEffect(&re_snake);
	
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