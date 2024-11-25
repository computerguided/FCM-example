#ifndef FCM_EXAMPLE_DOOR_CONTROLLER_H
#define FCM_EXAMPLE_DOOR_CONTROLLER_H

#include "FcmFunctionalComponent.h"
#include "SensorHandler.h"

FCM_FUNCTIONAL_COMPONENT(DoorController,

    // Handler references
    std::shared_ptr<SensorHandler> sensorHandler;

    // Settings
    FcmTime openDoorTimeoutMs{};

    // State variables
    int openDoorTimerId = -1;
    uint doorId = -1;
    bool lockState = false;
    bool doorState = false;

    // Local functions
    void sendDoorStateChangedInd();
    void sendDoorLockChangedInd();
);

#endif //FCM_EXAMPLE_DOOR_CONTROLLER_H
