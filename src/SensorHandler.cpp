#include "SensorHandler.h"

// ---------------------------------------------------------------------------------------------------------------------
// Interfaces
// ---------------------------------------------------------------------------------------------------------------------
#include "Sensing.h"

// ---------------------------------------------------------------------------------------------------------------------
void SensorHandler::initialize()
{
    setSetting<uint>("numDoors", this->numDoors);

    // Mockup implementation:
    // - 'Detect' the number of doors.

    for (uint i = 0; i < numDoors; i++)
    {
        // Mockup implementation:
        // - Reply with Sensing:DoorDetectedInd

        FCM_PREPARE_MESSAGE(doorDetectedInd, Sensing, DoorDetectedInd);
        doorDetectedInd->doorId = i;
        FCM_SEND_MESSAGE(doorDetectedInd, i);
    }
}

// ---------------------------------------------------------------------------------------------------------------------
void SensorHandler::enableDoorSensor(uint doorId)
{
    // Mockup implementation:
    // - Reply with Sensing:DoorSensorInd using the door id as index.

    FCM_PREPARE_MESSAGE(doorSensorInd, Sensing, DoorSensorInd);
    doorSensorInd->open = false;
    FCM_SEND_MESSAGE(doorSensorInd, doorId);
}

// ---------------------------------------------------------------------------------------------------------------------
void SensorHandler::enableLockSensor(uint doorId)
{
    // Mockup implementation:
    // - Reply with Sensing:LockSensorInd using the door id as index.

    FCM_PREPARE_MESSAGE(lockSensorInd, Sensing, LockSensorInd);
    lockSensorInd->locked = false;
    FCM_SEND_MESSAGE(lockSensorInd, doorId);
}

// ---------------------------------------------------------------------------------------------------------------------
void SensorHandler::lock(uint doorId)
{
    // Mockup implementation:
    // - Reply with Sensing:LockSensorInd using the door id as index.
    sendLockSensorInd(doorId, true);
}

// ---------------------------------------------------------------------------------------------------------------------
void SensorHandler::unlock(uint doorId)
{
    // Mockup implementation:
    // - Reply with Sensing:LockSensorInd using the door id as index.
    sendLockSensorInd(doorId, false);
}

// ---------------------------------------------------------------------------------------------------------------------
void SensorHandler::sendDoorSensorInd(uint doorId, bool open)
{
    // Mockup implementation:
    // - Reply with Sensing:DoorSensorInd using the door id as index.

    FCM_PREPARE_MESSAGE(doorSensorInd, Sensing, DoorSensorInd);
    doorSensorInd->open = open;
    FCM_SEND_MESSAGE(doorSensorInd, doorId);
}

// ---------------------------------------------------------------------------------------------------------------------
void SensorHandler::sendLockSensorInd(uint doorId, bool locked)
{
    // Mockup implementation:
    // - Reply with Sensing:LockSensorInd using the door id as index.

    FCM_PREPARE_MESSAGE(lockSensorInd, Sensing, LockSensorInd);
    lockSensorInd->locked = locked;
    FCM_SEND_MESSAGE(lockSensorInd, doorId);
}
