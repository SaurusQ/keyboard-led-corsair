
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
	EffectBall ball;
	EffectRandom random;
	EffectStatic e_static;
	device.addEffect(&clear);
	device.addEffect(&ball);
	device.start();
	while(1){}
}