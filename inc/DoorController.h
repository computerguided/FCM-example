#ifndef FCM_EXAMPLE_DOOR_CONTROLLER_H
#define FCM_EXAMPLE_DOOR_CONTROLLER_H

#include "FcmFunctionalComponent.h"
#include "SensorHandler.h"

class DoorController : public FcmFunctionalComponent
{
public:
    using FcmFunctionalComponent::FcmFunctionalComponent;
    void initialize() override;

protected:
    // Handler references
    std::shared_ptr<SensorHandler> sensorHandler;

    // Settings
    FcmTime openDoorTimeoutMs{};

    // State variables
    int openDoorTimerId = -1;
    uint doorId = -1;
    bool lockState = false;
    bool doorState = false;

    void setTransitions() override;
    void setChoicePoints() override;
    void setStates() override;

private:
    // Local functions
    void sendDoorStateChangedInd();
    void sendDoorLockChangedInd();
};

#endif //FCM_EXAMPLE_DOOR_CONTROLLER_H
