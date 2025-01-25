#ifndef DOORS_CONTROLLING_SYSTEM_BACKEND_INTERFACE_H
#define DOORS_CONTROLLING_SYSTEM_BACKEND_INTERFACE_H

#include <string>
#include <thread>

#include "FcmAsyncInterfaceHandler.h"
#include "SensorHandler.h" // For testing purposes

FCM_ASYNC_INTERFACE_HANDLER(BackendInterface,
    void connect(const std::string& url);
    void keepAlive() { /* TODO */ };
    void doorLockChanged(uint doorId, bool locked) { /* TODO */ (void)doorId; (void)locked; };
    void doorStateChanged(uint doorId, bool open) { /* TODO */ (void)doorId; (void)open; };
    void alarm(uint doorId, const std::string& alarm) 
    {
        logInfo("Door " + std::to_string(doorId) + ": " + alarm);
    };
    void error(uint doorId, const std::string& error)
    {
        logError("Door " + std::to_string(doorId) + ": " + error);
    };

    // Reference to SensorHandler for testing purposes
    std::shared_ptr<SensorHandler> sensorHandler;

    std::thread commandLineThread;
    void commandLineInput();
    void executeCommand(const std::string& command, uint doorId = 0, uint tagId = 0);
);

#endif //DOORS_CONTROLLING_SYSTEM_BACKEND_INTERFACE_H
