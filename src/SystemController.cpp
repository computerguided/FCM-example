#include <iostream>
#include <string>

#include "SystemController.h"

// ---------------------------------------------------------------------------------------------------------------------
// Interfaces
// ---------------------------------------------------------------------------------------------------------------------
#include "Control.h"
#include "Commands.h"
#include "Admin.h"

// ---------------------------------------------------------------------------------------------------------------------
void SystemController::initialize()
{
    setSetting<uint>("numDoors", numDoors);
    setSetting<std::shared_ptr<BackendInterface>>("Backend Interface", backendInterface);
}

// ---------------------------------------------------------------------------------------------------------------------
// Set states
// ---------------------------------------------------------------------------------------------------------------------
void SystemController::setStates()
{
    states =
    {
        "Awaiting Doors",
        "All Doors Detected?",
        "Initializing",
        "Connecting",
        "Ready",
        "Processing"
    };
}

// ---------------------------------------------------------------------------------------------------------------------
void SystemController::setTransitions()
{
    FCM_ADD_TRANSITION("Awaiting Doors", Control, DoorDetectedInd, "All Doors Detected?",
    {
        detectedDoors.push_back(message.doorId);
    });
    FCM_ADD_TRANSITION("All Doors Detected?", Logical, Yes, "Initializing",
    {
        FCM_PREPARE_MESSAGE(backendUrlReq, Admin, BackendUrlReq);
        FCM_SEND_MESSAGE(backendUrlReq);
    });
    FCM_ADD_TRANSITION("All Doors Detected?", Logical, No, "Awaiting Doors",
    {
        // NOP
    });
    FCM_ADD_TRANSITION("Initializing", Admin, BackendUrlRsp, "Connecting",
    {
        backendInterface->connect(message.url);
    });
    FCM_ADD_TRANSITION("Connecting", Commands, ConnectedInd, "Ready",
    {
        for (int i = 0; i < detectedDoors.size(); i++)
        {
            FCM_PREPARE_MESSAGE(releaseDoorInd, Control, ReleaseDoorInd);
            FCM_SEND_MESSAGE(releaseDoorInd, i);
        }
    });
    FCM_ADD_TRANSITION("Ready", Commands, LockDoorInd, "Door Found?",
    {
        lastDoorIndex = findDoorIndex(message.doorId);
        lastDoorId = message.doorId;
    });
    FCM_ADD_TRANSITION("Ready", Commands, UnlockDoorInd, "Door Found?",
    {
        lastDoorIndex = findDoorIndex(message.doorId);
        lastDoorId = message.doorId;
    });
    FCM_ADD_TRANSITION("Ready", Commands, AddTagInd, "Door Found?",
    {
        lastDoorIndex = findDoorIndex(message.doorId);
        lastDoorId = message.doorId;
    });
    FCM_ADD_TRANSITION("Ready", Commands, RemoveTagInd, "Door Found?",
    {
        lastDoorIndex = findDoorIndex(message.doorId);
        lastDoorId = message.doorId;
    });
    FCM_ADD_TRANSITION("Ready", Control, DoorStateChangedInd, "Ready",
    {
        FCM_PREPARE_MESSAGE(doorStateChangedInd, Admin, DoorStateChangedInd);
        doorStateChangedInd->doorId = message.doorId;
        doorStateChangedInd->open = message.open;
        FCM_SEND_MESSAGE(doorStateChangedInd);

        backendInterface->doorStateChanged(message.doorId, message.open);
    });
    FCM_ADD_TRANSITION("Ready", Control, DoorLockChangedInd, "Ready",
    {
        FCM_PREPARE_MESSAGE(doorLockChanged, Admin, DoorLockChangedInd);
        doorLockChanged->doorId = message.doorId;
        doorLockChanged->locked = message.locked;
        FCM_SEND_MESSAGE(doorLockChanged);
        backendInterface->doorLockChanged(message.doorId, message.locked);
    });
    FCM_ADD_TRANSITION("Ready", Control, ErrorInd, "Ready",
    {
        backendInterface->error(message.doorId, message.error);
    });
    FCM_ADD_TRANSITION("Ready", Control, AlarmInd, "Ready",
    {
        backendInterface->alarm(message.doorId, message.alarm);
    });
    FCM_ADD_TRANSITION("Door Found?", Logical, Yes, "Processing",
    {
        resendLastReceivedMessage();
    });
    FCM_ADD_TRANSITION("Door Found?", Logical, No, "Ready",
    {
        std::string error = "Door with id " + std::to_string(lastDoorId) + " not found!";
        backendInterface->error(lastDoorId, error);
    });
    FCM_ADD_TRANSITION("Processing", Commands, LockDoorInd, "Ready",
    {
        FCM_PREPARE_MESSAGE(setLockInd, Control, SetLockInd);
        setLockInd->locked = true;
        FCM_SEND_MESSAGE(setLockInd, lastDoorIndex);
    });
    FCM_ADD_TRANSITION("Processing", Commands, UnlockDoorInd, "Ready",
    {
        FCM_PREPARE_MESSAGE(setLockInd, Control, SetLockInd);
        setLockInd->locked = false;
        FCM_SEND_MESSAGE(setLockInd, lastDoorIndex);
    });
    FCM_ADD_TRANSITION("Processing", Commands, AddTagInd, "Ready",
    {
        FCM_PREPARE_MESSAGE(addTagInd, Control, AddTagInd);
        addTagInd->tagId = message.tagId;
        FCM_SEND_MESSAGE(addTagInd, lastDoorIndex);
    });
    FCM_ADD_TRANSITION("Processing", Commands, RemoveTagInd, "Ready",
    {
        FCM_PREPARE_MESSAGE(removeTagInd, Control, RemoveTagInd);
        removeTagInd->tagId = message.tagId;
        FCM_SEND_MESSAGE(removeTagInd, lastDoorIndex);
    });
    FCM_ADD_TRANSITION("*", Commands, KeepAliveInd, "H",
    {
        backendInterface->keepAlive();
    });
}

// ---------------------------------------------------------------------------------------------------------------------
void SystemController::setChoicePoints()
{
    FCM_ADD_CHOICE_POINT("All Doors Detected?",
    {
        return detectedDoors.size() == numDoors;
    });
    FCM_ADD_CHOICE_POINT("Door Found?",
    {
        return lastDoorIndex != -1;
    });
}

// ---------------------------------------------------------------------------------------------------------------------
// Local functions
// ---------------------------------------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------------------------------------
int SystemController::findDoorIndex(uint doorId)
{
    for (int i = 0; i < detectedDoors.size(); i++)
    {
        if (detectedDoors[i] == doorId)
        {
            return i;
        }
    }
    return -1;
}

