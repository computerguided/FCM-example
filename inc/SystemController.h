#ifndef FCM_EXAMPLE_SYSTEM_CONTROLLER_H
#define FCM_EXAMPLE_SYSTEM_CONTROLLER_H

#include "FcmFunctionalComponent.h"
#include "BackendInterface.h"

FCM_FUNCTIONAL_COMPONENT(SystemController,

    std::shared_ptr<BackendInterface> backendInterface;
    uint numDoors{};
    std::vector<uint> detectedDoors;
    int lastDoorIndex = -1;
    uint lastDoorId = 0;
    int findDoorIndex(uint doorId);
);

#endif //FCM_EXAMPLE_SYSTEM_CONTROLLER_H
