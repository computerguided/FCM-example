#ifndef DOORS_CONTROLLING_SYSTEM_BACKEND_INTERFACE_H
#define DOORS_CONTROLLING_SYSTEM_BACKEND_INTERFACE_H

#include <string>
#include <thread>

#include "FcmAsyncInterfaceHandler.h"
#include "SensorHandler.h" // For testing purposes

class BackendInterface : public FcmAsyncInterfaceHandler
{
public:
    using FcmAsyncInterfaceHandler::FcmAsyncInterfaceHandler;

    void connect(const std::string& url);
    void keepAlive() { /* TODO */ };
    void doorLockChanged(uint doorId, bool locked) { /* TODO */ };
    void doorStateChanged(uint doorId, bool open) { /* TODO */ };
    void alarm(uint doorId, const std::string& alarm) 
    {
        logInfo("Door " + std::to_string(doorId) + ": " + alarm);
    };
    void error(uint doorId, const std::string& error)
    {
        logError("Door " + std::to_string(doorId) + ": " + error);
    };

    void initialize() override;

    // Reference to SensorHandler for testing purposes
    std::shared_ptr<SensorHandler> sensorHandler;

private:
    std::thread commandLineThread;
    void commandLineInput();
    void executeCommand(const std::string& command, uint doorId = 0, uint tagId = 0);
};

#endif //DOORS_CONTROLLING_SYSTEM_BACKEND_INTERFACE_H
