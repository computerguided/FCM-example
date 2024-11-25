#ifndef DOORS_CONTROLLING_SYSTEM_ADMINISTRATOR_H
#define DOORS_CONTROLLING_SYSTEM_ADMINISTRATOR_H

#include "FcmFunctionalComponent.h"
#include "ConfigurationDatabase.h"

FCM_FUNCTIONAL_COMPONENT(Administrator,
    std::shared_ptr<ConfigurationDatabase> configurationDatabase;
    std::vector<std::string> pendingEvents;
);

#endif //DOORS_CONTROLLING_SYSTEM_ADMINISTRATOR_H
