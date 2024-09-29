#ifndef DOORS_CONTROLLING_SYSTEM_CONFIGURATION_DATABASE_H
#define DOORS_CONTROLLING_SYSTEM_CONFIGURATION_DATABASE_H

#include "FcmAsyncInterfaceHandler.h"

class ConfigurationDatabase : public FcmAsyncInterfaceHandler
{
public:
    explicit ConfigurationDatabase(const std::string& nameParam,
                                   const FcmSettings& settingsParam = {});

    void initDatabase();
    void getBackendUrl();
    void storeEvent(const std::string& event);
};

#endif //DOORS_CONTROLLING_SYSTEM_CONFIGURATION_DATABASE_H
