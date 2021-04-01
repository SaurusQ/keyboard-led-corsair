
#include "device.hpp"

Device::Device(unsigned int fps)
    : fps_(fps)
    , lightingThreadRunning_(false)
{
    this->reInit();
    std::cout << "Successful init" << std::endl;
}

Device::~Device()
{
    initialized_ = false;
    CorsairReleaseControl(CAM_ExclusiveLightingControl);
    delete pColors_; // TODO necessary?
}

bool Device::reInit()
{
    initialized_ = false;
    CorsairPerformProtocolHandshake();
    auto error = CorsairGetLastError();
    if(error)
    {
        std::cerr << "Hanshake failed: " << this->errToString(error) << std::endl;
        return false;
    }
    std::cout << "Handshake success" << std::endl;

    CorsairRequestControl(CAM_ExclusiveLightingControl);
    error = CorsairGetLastError();
    if(error)
    {
        std::cerr << "Requesting control failed: " << this->errToString(error) << std::endl;
        return false;
    }
    std::cout << "Req contr success" << std::endl;

    CorsairLedPositions* pos = CorsairGetLedPositions();
    error = CorsairGetLastError();
    if(error)
    {
        std::cerr << "Getting led postions failed: " << this->errToString(error) << std::endl;
        return false;
    }
    pPositions_ = pos->pLedPosition;
    numKeys_ = pos->numberOfLed;
    pColors_ = this->posToColor(pPositions_, numKeys_);
    std::cout << "PosToCol success" << std::endl;

    initialized_ = true;
    return true;
}

void Device::start()
{
    lightingThreadRunning_ = true;
    lightingThread_ = std::thread([this]
    {
        std::chrono::high_resolution_clock::time_point startTime = std::chrono::high_resolution_clock::now();
        std::chrono::nanoseconds diff;
        const std::chrono::nanoseconds frameTime(static_cast<uint64_t>(1000000000 / fps_));
        while(this->lightingThreadRunning_)
        {
            diff = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - startTime);
            if(frameTime <= diff)
            {
                this->run();
                startTime += frameTime;
            }
            else std::this_thread::sleep_for(diff);
        }
    });
}

void Device::stop()
{
    lightingThreadRunning_ = false;
    lightingThread_.join();
}

void Device::run()
{
    /*CorsairLedColor ledColor = {CLI_Invalid, 12, 123, 12};
    for(int i = 0; i < 200; i++)
    {
        ledColor.ledId = (CorsairLedId)i;
        CorsairSetLedsColors(1, &ledColor);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }*/
    for(auto pEff : pEffects_)
    {
        pEff->run(pPositions_, pColors_, numKeys_);
    }
    CorsairSetLedsColorsBufferByDeviceIndex(0, numKeys_, pColors_);
    CorsairSetLedsColorsFlushBuffer();
}

void Device::addEffect(Effect* pEff)
{
    pEffects_.push_back(pEff);
}

CorsairLedColor* Device::posToColor(CorsairLedPosition* pPos, size_t len)
{
    CorsairLedColor* pCol = new CorsairLedColor[len];
    for(int i = 0; i < len; i++)
    {
        pCol[i] = CorsairLedColor{pPos[i].ledId, 0, 0, 0};
    }
    return pCol;
}

std::string Device::errToString(CorsairError err)
{
	switch (err) {
	case CE_Success :
		return "CE_Success";
	case CE_ServerNotFound:
		return "CE_ServerNotFound";
	case CE_NoControl:
		return "CE_NoControl";
	case CE_ProtocolHandshakeMissing:
		return "CE_ProtocolHandshakeMissing";
	case CE_IncompatibleProtocol:
		return "CE_IncompatibleProtocol";
	case CE_InvalidArguments:
		return "CE_InvalidArguments";
	default:
		return "unknown error";
	}
}
