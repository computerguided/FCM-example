#ifndef DOORS_CONTROLLING_SYSTEM_SENSOR_HANDLER_H
#define DOORS_CONTROLLING_SYSTEM_SENSOR_HANDLER_H

#include <sys/types.h>

#include "FcmAsyncInterfaceHandler.h"

class SensorHandler : public FcmAsyncInterfaceHandler
{
public:
    using FcmAsyncInterfaceHandler::FcmAsyncInterfaceHandler;

    void initialize() override;

    void enableLockSensor(uint doorId);
    void enableDoorSensor(uint doorId);
    void lock(uint doorId);
    void unlock(uint doorId);
    void addTag(uint doorId, uint tagId) { /* TODO */ };
    void removeTag(uint doorId, uint tagId) { /* TODO */ };

    // Functions for testing
    void sendDoorSensorInd(uint doorId, bool open);
    void sendLockSensorInd(uint doorId, bool locked);

protected:
    uint numDoors{};
};
#endif //DOORS_CONTROLLING_SYSTEM_SENSOR_HANDLER_H
