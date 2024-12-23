#ifndef FCM_DOORS_CONTROLLING_SYSTEM_H
#define FCM_DOORS_CONTROLLING_SYSTEM_H

#include <iostream>

#include "FcmDevice.h"

// Asynchronous Interface Handlers
#include "BackendInterface.h"
#include "SensorHandler.h"
#include "ConfigurationDatabase.h"

// Functional components
#include "Administrator.h"
#include "SystemController.h"
#include "DoorController.h"

class DoorsControllingSystem : public FcmDevice
{
public:
    explicit DoorsControllingSystem(uint numDoors) : FcmDevice(), numDoors(numDoors) {}
    void initialize() override;

private:
    uint numDoors;

    FcmLogFunction logTransition = [](const std::string& message)
    {
        std::cout << message << std::endl;
    };

    FcmLogFunction logDebug = [](const std::string& message)
    {
        std::cout << message << std::endl;
    };

    FcmLogFunction logInfo = [](const std::string& message)
    {
        std::cout << message << std::endl;
    };

    FcmLogFunction logWarning = [](const std::string& message)
    {
        std::cout << message << std::endl;
    };

    FcmLogFunction logError = [](const std::string& message)
    {
        std::cout << message << std::endl;
    };

    FcmLogFunction fatalError = [](const std::string& message)
    {
        std::cout << message << std::endl;
        exit(EXIT_FAILURE);
    };
};

#endif //FCM_DOORS_CONTROLLING_SYSTEM_H
