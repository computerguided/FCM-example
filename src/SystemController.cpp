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
    addTransitionFunction<Control::DoorDetectedInd>("Awaiting Doors", "All Doors Detected?", [this](const auto& message)
    {
        detectedDoors.push_back(message.doorId);
    });
    addTransitionFunction<Logical::Yes>("All Doors Detected?", "Initializing", [this](const auto& message)
    {
        auto backendUrlReq = prepareMessage<Admin::BackendUrlReq>();
        sendMessage(backendUrlReq);
    });
    addTransitionFunction<Logical::No>("All Doors Detected?", "Awaiting Doors", [this](const auto& message)
    {
        (void)this;
    });
    addTransitionFunction<Admin::BackendUrlRsp>("Initializing", "Connecting", [this](const auto& message)
    {
        backendInterface->connect(message.url);
    });
    addTransitionFunction<Commands::ConnectedInd>("Connecting", "Ready", [this](const auto& message)
    {
        for (int i = 0; i < detectedDoors.size(); i++)
        {
            auto releaseDoorInd = prepareMessage<Control::ReleaseDoorInd>();
            sendMessage(releaseDoorInd, i);
        }
    });
    addTransitionFunction<Commands::LockDoorInd>("Ready", "Door Found?", [this](const auto& message)
    {
        lastDoorIndex = findDoorIndex(message.doorId);
        lastDoorId = message.doorId;
    });
    addTransitionFunction<Commands::UnlockDoorInd>("Ready", "Door Found?", [this](const auto& message)
    {
        lastDoorIndex = findDoorIndex(message.doorId);
        lastDoorId = message.doorId;
    });
    addTransitionFunction<Commands::AddTagInd>("Ready", "Door Found?", [this](const auto& message)
    {
        lastDoorIndex = findDoorIndex(message.doorId);
        lastDoorId = message.doorId;
    });
    addTransitionFunction<Commands::RemoveTagInd>("Ready", "Door Found?", [this](const auto& message)
    {
        lastDoorIndex = findDoorIndex(message.doorId);
        lastDoorId = message.doorId;
    });
    addTransitionFunction<Control::DoorStateChangedInd>("Ready", "Ready", [this](const auto& message)
    {
        auto doorStateChangedInd = prepareMessage<Admin::DoorStateChangedInd>();
        doorStateChangedInd->doorId = message.doorId;
        doorStateChangedInd->open = message.open;
        sendMessage(doorStateChangedInd);
        backendInterface->doorStateChanged(message.doorId, message.open);
    });
    addTransitionFunction<Control::DoorLockChangedInd>("Ready", "Ready", [this](const auto& message)
    {
        auto doorLockChanged = prepareMessage<Admin::DoorLockChangedInd>();
        doorLockChanged->doorId = message.doorId;
        doorLockChanged->locked = message.locked;
        sendMessage(doorLockChanged);
        backendInterface->doorLockChanged(message.doorId, message.locked);
    });
    addTransitionFunction<Control::ErrorInd>("Ready", "Ready", [this](const auto& message)
    {
        backendInterface->error(message.doorId, message.error);
    });
    addTransitionFunction<Control::AlarmInd>("Ready", "Ready", [this](const auto& message)
    {
        backendInterface->alarm(message.doorId, message.alarm);
    });
    addTransitionFunction<Logical::Yes>("Door Found?", "Processing", [this](const auto& message)
    {
        resendLastReceivedMessage();
    });
    addTransitionFunction<Logical::No>("Door Found?", "Ready", [this](const auto& message)
    {
        std::string error = "Door with id " + std::to_string(lastDoorId) + " not found!";
        backendInterface->error(lastDoorId, error);
    });
    addTransitionFunction<Commands::LockDoorInd>("Processing", "Ready", [this](const auto& message)
    {
        auto setLockInd = prepareMessage<Control::SetLockInd>();
        setLockInd->locked = true;
        sendMessage(setLockInd, lastDoorIndex);
    });
    addTransitionFunction<Commands::UnlockDoorInd>("Processing", "Ready", [this](const auto& message)
    {
        auto setLockInd = prepareMessage<Control::SetLockInd>();
        setLockInd->locked = false;
        sendMessage(setLockInd, lastDoorIndex);
    });
    addTransitionFunction<Commands::AddTagInd>("Processing", "Ready", [this](const auto& message)
    {
        auto addTagInd = prepareMessage<Control::AddTagInd>();
        addTagInd->tagId = message.tagId;
        sendMessage(addTagInd, lastDoorIndex);
    });
    addTransitionFunction<Commands::RemoveTagInd>("Processing", "Ready", [this](const auto& message)
    {
        auto removeTagInd = prepareMessage<Control::RemoveTagInd>();
        removeTagInd->tagId = message.tagId;
        sendMessage(removeTagInd, lastDoorIndex);
    });
    addTransitionFunction<Commands::KeepAliveInd>("*", "H", [this](const auto& message)
    {
        backendInterface->keepAlive();
    });
}

// ---------------------------------------------------------------------------------------------------------------------
void SystemController::setChoicePoints()
{
    addChoicePoint("All Doors Detected?", [this]()
    {
        return detectedDoors.size() == numDoors;
    });
    addChoicePoint("Door Found?", [this]()
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

