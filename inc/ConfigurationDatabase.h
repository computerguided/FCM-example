#ifndef DOORS_CONTROLLING_SYSTEM_CONFIGURATION_DATABASE_H
#define DOORS_CONTROLLING_SYSTEM_CONFIGURATION_DATABASE_H

#include "FcmAsyncInterfaceHandler.h"

FCM_ASYNC_INTERFACE_HANDLER(ConfigurationDatabase,

    void initDatabase();
    void getBackendUrl();
    void storeEvent(const std::string& event);
);

#endif //DOORS_CONTROLLING_SYSTEM_CONFIGURATION_DATABASE_H
