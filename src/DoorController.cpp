#include "DoorController.h"

// ---------------------------------------------------------------------------------------------------------------------
// Interfaces
// ---------------------------------------------------------------------------------------------------------------------
#include "Sensing.h"
#include "Control.h"

// ---------------------------------------------------------------------------------------------------------------------
void DoorController::initialize()
{
    setSetting<FcmTime>("openDoorTimeoutMs", openDoorTimeoutMs);
    setSetting<std::shared_ptr<SensorHandler>>("Sensor Handler", sensorHandler);
}

// ---------------------------------------------------------------------------------------------------------------------
// Set the states
// ---------------------------------------------------------------------------------------------------------------------
void DoorController::setStates()
{
    states =
    {
        "Idle",
        "Standby",
        "Await Door Sensor",
        "Closed?",
        "Is Locked?",
        "Open",
        "Unlocked",
        "Locked",
        "Unlocking",
        "Locking",
        "Await Lock Sensor"
    };
}

// ---------------------------------------------------------------------------------------------------------------------
void DoorController::setTransitions()
{
    FCM_ADD_TRANSITION("Idle", Sensing, DoorDetectedInd, "Standby",
        doorId = message.doorId;
        FCM_PREPARE_MESSAGE(doorDetectedInd, Control, DoorDetectedInd);
        doorDetectedInd->doorId = doorId;
        FCM_SEND_MESSAGE(doorDetectedInd);
    );
    FCM_ADD_TRANSITION("Standby", Control, ReleaseDoorInd, "Await Door Sensor",
        sensorHandler->enableDoorSensor(doorId);
    );
    FCM_ADD_TRANSITION("Await Door Sensor", Sensing, DoorSensorInd, "Closed?",
        doorState = message.open;
        sendDoorStateChangedInd();
    );
    FCM_ADD_TRANSITION("Closed?", Logical, Yes, "Await Lock Sensor",
        sensorHandler->enableLockSensor(doorId);
    );
    FCM_ADD_TRANSITION("Closed?", Logical, No, "Open",
        openDoorTimerId = setTimeout(openDoorTimeoutMs);
    );
    FCM_ADD_TRANSITION("Await Lock Sensor", Sensing, LockSensorInd, "Is Locked?",
        lockState = message.locked;
        sendDoorLockChangedInd();
    );
    FCM_ADD_TRANSITION("Is Locked?", Logical, Yes, "Locked",
        // NOP
    );
    FCM_ADD_TRANSITION("Is Locked?", Logical, No, "Unlocked",
        // NOP
    );
    FCM_ADD_TRANSITION("Open", Sensing, DoorSensorInd, "Unlocked",
        doorState = message.open;
        sendDoorStateChangedInd();
        cancelTimeout(openDoorTimerId);
    );
    FCM_ADD_TRANSITION("Open", Control, SetLockInd, "Open",
        FCM_PREPARE_MESSAGE(errorInd, Control, ErrorInd);
        errorInd->doorId = doorId;
        errorInd->error = "Door lock cannot be changed when open";
        FCM_SEND_MESSAGE(errorInd);
    );
    FCM_ADD_TRANSITION("Open", Timer, Timeout, "Open",
        FCM_PREPARE_MESSAGE(alarmInd, Control, AlarmInd);
        alarmInd->doorId = doorId;
        alarmInd->alarm = "Open for too long";
        FCM_SEND_MESSAGE(alarmInd);
    );
    FCM_ADD_TRANSITION("Unlocked", Sensing, DoorSensorInd, "Open",
        doorState = message.open;
        sendDoorStateChangedInd();
        openDoorTimerId = setTimeout(openDoorTimeoutMs);
    );
    FCM_ADD_TRANSITION("Unlocked", Control, SetLockInd, "Locking",
        sensorHandler->lock(doorId);
    );
    FCM_ADD_TRANSITION("Locking", Sensing, LockFailInd, "Unlocked",
        FCM_PREPARE_MESSAGE(errorInd, Control, ErrorInd);
        errorInd->doorId = doorId;
        errorInd->error = "Locking failed";
        FCM_SEND_MESSAGE(errorInd);
    );
    FCM_ADD_TRANSITION("Locked", Control, SetLockInd, "Unlocking",
        sensorHandler->unlock(doorId);
    );
    FCM_ADD_TRANSITION("Locked", Control, AddTagInd, "Locked",
        sensorHandler->addTag(doorId, message.tagId);
    );
    FCM_ADD_TRANSITION("Locked", Control, RemoveTagInd, "Locked",
        sensorHandler->removeTag(doorId, message.tagId);
    );
    FCM_ADD_TRANSITION("Locked", Sensing, LockSensorInd, "Unlocked",
        lockState = message.locked;
        sendDoorLockChangedInd();
    );
    FCM_ADD_TRANSITION("Unlocking", Sensing, LockSensorInd, "Unlocked",
        lockState = message.locked;
        sendDoorLockChangedInd();
    );
    FCM_ADD_TRANSITION("Unlocking", Sensing, UnlockFailInd, "Locked",
        FCM_PREPARE_MESSAGE(errorInd, Control, ErrorInd);
        errorInd->doorId = doorId;
        errorInd->error = "Unlocking failed";
        FCM_SEND_MESSAGE(errorInd);
    );
    FCM_ADD_MULTIPLE_STATES_TRANSITION(({"Unlocked", "Locking"}), Sensing, LockSensorInd, "Locked",
       lockState = message.locked;
       sendDoorLockChangedInd();
    );
}

// ---------------------------------------------------------------------------------------------------------------------
void DoorController::setChoicePoints()
{
    FCM_ADD_CHOICE_POINT("Closed?",
        return !doorState;
    );
    FCM_ADD_CHOICE_POINT("Is Locked?",
        return lockState;
    );
}

// ---------------------------------------------------------------------------------------------------------------------
void DoorController::sendDoorLockChangedInd()
{
    FCM_PREPARE_MESSAGE(doorLockChangedInd, Control, DoorLockChangedInd);
    doorLockChangedInd->doorId = doorId;
    doorLockChangedInd->locked = lockState;
    FCM_SEND_MESSAGE(doorLockChangedInd);
}

// ---------------------------------------------------------------------------------------------------------------------
void DoorController::sendDoorStateChangedInd()
{
    FCM_PREPARE_MESSAGE(doorSensorInd, Control, DoorStateChangedInd);
    doorSensorInd->doorId = doorId;
    doorSensorInd->open = doorState;
    FCM_SEND_MESSAGE(doorSensorInd);
}