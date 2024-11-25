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

        auto doorDetectedInd = prepareMessage<Sensing::DoorDetectedInd>();
        doorDetectedInd->doorId = i;
        sendMessage(doorDetectedInd, i);
    }
}

// ---------------------------------------------------------------------------------------------------------------------
void SensorHandler::enableDoorSensor(uint doorId)
{
    // Mockup implementation:
    // - Reply with Sensing:DoorSensorInd using the door id as index.

    auto doorSensorInd = prepareMessage<Sensing::DoorSensorInd>();
    doorSensorInd->open = false;
    sendMessage(doorSensorInd, doorId);
}

// ---------------------------------------------------------------------------------------------------------------------
void SensorHandler::enableLockSensor(uint doorId)
{
    // Mockup implementation:
    // - Reply with Sensing:LockSensorInd using the door id as index.

    auto lockSensorInd = prepareMessage<Sensing::LockSensorInd>();
    lockSensorInd->locked = false;
    sendMessage(lockSensorInd, doorId);
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

    auto doorSensorInd = prepareMessage<Sensing::DoorSensorInd>();
    doorSensorInd->open = open;
    sendMessage(doorSensorInd, doorId);
}

// ---------------------------------------------------------------------------------------------------------------------
void SensorHandler::sendLockSensorInd(uint doorId, bool locked)
{
    // Mockup implementation:
    // - Reply with Sensing:LockSensorInd using the door id as index.

    auto lockSensorInd = prepareMessage<Sensing::LockSensorInd>();
    lockSensorInd->locked = locked;
    sendMessage(lockSensorInd, doorId);
}
