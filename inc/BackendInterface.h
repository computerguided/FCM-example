#ifndef DOORS_CONTROLLING_SYSTEM_BACKEND_INTERFACE_H
#define DOORS_CONTROLLING_SYSTEM_BACKEND_INTERFACE_H

#include <string>
#include <thread>

#include "FcmAsyncInterfaceHandler.h"
#include "SensorHandler.h" // For testing purposes

class BackendInterface : public FcmAsyncInterfaceHandler
{
public:

    explicit BackendInterface(const std::string& nameParam,
                              const FcmSettings& settingsParam = {})
        : FcmAsyncInterfaceHandler(nameParam, settingsParam) { /* TODO */ };

    void connect(const std::string& url);
    void keepAlive() { /* TODO */ };
    void doorLockChanged(uint doorId, bool locked) { /* TODO */ };
    void doorStateChanged(uint doorId, bool open) { /* TODO */ };
    void alarm(uint doorId, const std::string& alarm) { logInfo( alarm); };
    void error(uint doorId, const std::string& error) { logError( error); };

    void initialize() override;

    // Reference to SensorHandler for testing purposes
    std::shared_ptr<SensorHandler> sensorHandler;
    void setSensorHandler(std::shared_ptr<SensorHandler>& handler)
    {
        sensorHandler = handler;
    }

private:
    std::thread commandLineThread;
    void commandLineInput();
    void executeCommand(const std::string& command, uint doorId = 0, uint tagId = 0);
};

#endif //DOORS_CONTROLLING_SYSTEM_BACKEND_INTERFACE_H
