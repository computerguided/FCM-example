#ifndef DOORS_CONTROLLING_SYSTEM_ADMINISTRATOR_H
#define DOORS_CONTROLLING_SYSTEM_ADMINISTRATOR_H

#include "FcmFunctionalComponent.h"
#include "ConfigurationDatabase.h"

// Create an Administrator class as subclass of FcmFunctionalComponent
FCM_FUNCTIONAL_COMPONENT(Administrator,
    // State variables
    std::shared_ptr<ConfigurationDatabase> configurationDatabase;
    std::vector<std::string> pendingEvents;
);

#endif //DOORS_CONTROLLING_SYSTEM_ADMINISTRATOR_H
