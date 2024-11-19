#ifndef FCM_EXAMPLE_SYSTEM_CONTROLLER_H
#define FCM_EXAMPLE_SYSTEM_CONTROLLER_H

#include "FcmFunctionalComponent.h"
#include "BackendInterface.h"

class SystemController : public FcmFunctionalComponent
{
public:
    using FcmFunctionalComponent::FcmFunctionalComponent;
    void initialize() override;

protected:
    // Handler references
    std::shared_ptr<BackendInterface> backendInterface;

    // Settings
    uint numDoors{};

    // State variables
    std::vector<uint> detectedDoors;
    int lastDoorIndex = -1;
    uint lastDoorId = 0;

    void setTransitions() override;
    void setChoicePoints() override;
    void setStates() override;

    // Local functions
    int findDoorIndex(uint doorId);
};

#endif //FCM_EXAMPLE_SYSTEM_CONTROLLER_H
