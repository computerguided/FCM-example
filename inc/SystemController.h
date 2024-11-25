#ifndef FCM_EXAMPLE_SYSTEM_CONTROLLER_H
#define FCM_EXAMPLE_SYSTEM_CONTROLLER_H

#include "FcmFunctionalComponent.h"
#include "BackendInterface.h"

FCM_FUNCTIONAL_COMPONENT(SystemController,

    // Handler references
    std::shared_ptr<BackendInterface> backendInterface;

    // Settings
    uint numDoors{};

    // State variables
    std::vector<uint> detectedDoors;
    int lastDoorIndex = -1;
    uint lastDoorId = 0;

    // Local functions
    int findDoorIndex(uint doorId);
);

#endif //FCM_EXAMPLE_SYSTEM_CONTROLLER_H
