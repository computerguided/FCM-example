#ifndef DOORS_CONTROLLING_SYSTEM_SENSOR_HANDLER_H
#define DOORS_CONTROLLING_SYSTEM_SENSOR_HANDLER_H

#include <sys/types.h>

#include "FcmAsyncInterfaceHandler.h"

FCM_ASYNC_INTERFACE_HANDLER(SensorHandler,
    void enableLockSensor(uint doorId);
    void enableDoorSensor(uint doorId);
    void lock(uint doorId);
    void unlock(uint doorId);
    void addTag(uint doorId, uint tagId) { /* TODO */ };
    void removeTag(uint doorId, uint tagId) { /* TODO */ };

    // Functions for testing
    void sendDoorSensorInd(uint doorId, bool open);
    void sendLockSensorInd(uint doorId, bool locked);

    uint numDoors{};
);

#endif //DOORS_CONTROLLING_SYSTEM_SENSOR_HANDLER_H
