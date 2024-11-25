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
    addTransitionFunction<Sensing::DoorDetectedInd>("Idle", "Standby", [this](const auto& message)
    {
        doorId = message.doorId;
        auto doorDetectedInd = prepareMessage<Control::DoorDetectedInd>();
        doorDetectedInd->doorId = doorId;
        sendMessage(doorDetectedInd);
    });
    addTransitionFunction<Control::ReleaseDoorInd>("Standby", "Await Door Sensor", [this](const auto& message)
    {
        sensorHandler->enableDoorSensor(doorId);
    });
    addTransitionFunction<Sensing::DoorSensorInd>("Await Door Sensor", "Closed?", [this](const auto& message)
    {
        doorState = message.open;
        sendDoorStateChangedInd();
    });
    addTransitionFunction<Logical::Yes>("Closed?", "Await Lock Sensor", [this](const auto& message)
    {
        sensorHandler->enableLockSensor(doorId);
    });
    addTransitionFunction<Logical::No>("Closed?", "Open", [this](const auto& message)
    {
        openDoorTimerId = setTimeout(openDoorTimeoutMs);
    });
    addTransitionFunction<Sensing::LockSensorInd>("Await Lock Sensor", "Is Locked?", [this](const auto& message)
    {
        lockState = message.locked;
        sendDoorLockChangedInd();
    });
    addTransitionFunction<Logical::Yes>("Is Locked?", "Locked", [this](const auto& message)
    {
        (void)this;
    });
    addTransitionFunction<Logical::No>("Is Locked?", "Unlocked", [this](const auto& message)
    {
        (void)this;
    });
    addTransitionFunction<Sensing::DoorSensorInd>("Open", "Unlocked", [this](const auto& message)
    {
        doorState = message.open;
        sendDoorStateChangedInd();
        cancelTimeout(openDoorTimerId);
    });
    addTransitionFunction<Control::SetLockInd>("Open", "Open", [this](const auto& message)
    {
        auto errorInd = prepareMessage<Control::ErrorInd>();
        errorInd->doorId = doorId;
        errorInd->error = "Door lock cannot be changed when open";
        sendMessage(errorInd);
    });
    addTransitionFunction<Timer::Timeout>("Open", "Open", [this](const auto& message)
    {
        auto alarmInd = prepareMessage<Control::AlarmInd>();
        alarmInd->doorId = doorId;
        alarmInd->alarm = "Open for too long";
        sendMessage(alarmInd);
    });
    addTransitionFunction<Sensing::DoorSensorInd>("Unlocked", "Open", [this](const auto& message)
    {
        doorState = message.open;
        sendDoorStateChangedInd();
        openDoorTimerId = setTimeout(openDoorTimeoutMs);
    });
    addTransitionFunction<Control::SetLockInd>("Unlocked", "Locking", [this](const auto& message)
    {
        sensorHandler->lock(doorId);
    });
    addTransitionFunction<Sensing::LockFailInd>("Locking", "Unlocked", [this](const auto& message)
    {
        auto errorInd = prepareMessage<Control::ErrorInd>();
        errorInd->doorId = doorId;
        errorInd->error = "Locking failed";
        sendMessage(errorInd);
    });
    addTransitionFunction<Control::SetLockInd>("Locked", "Unlocking", [this](const auto& message)
    {
        sensorHandler->unlock(doorId);
    });
    addTransitionFunction<Control::AddTagInd>("Locked", "Locked", [this](const auto& message)
    {
        sensorHandler->addTag(doorId, message.tagId);
    });
    addTransitionFunction<Control::RemoveTagInd>("Locked", "Locked", [this](const auto& message)
    {
        sensorHandler->removeTag(doorId, message.tagId);
    });
    addTransitionFunction<Sensing::LockSensorInd>("Locked", "Unlocked", [this](const auto& message)
    {
        lockState = message.locked;
        sendDoorLockChangedInd();
    });
    addTransitionFunction<Sensing::LockSensorInd>("Unlocking", "Unlocked", [this](const auto& message)
    {
        lockState = message.locked;
        sendDoorLockChangedInd();
    });
    addTransitionFunction<Sensing::UnlockFailInd>("Unlocking", "Locked", [this](const auto& message)
    {
        auto errorInd = prepareMessage<Control::ErrorInd>();
        errorInd->doorId = doorId;
        errorInd->error = "Unlocking failed";
        sendMessage(errorInd);
    });
    addMultipleStatesTransition<Sensing::LockSensorInd>({"Unlocked", "Locking"}, "Locked", [this](const auto& message)
    {
        lockState = message.locked;
        sendDoorLockChangedInd();
    });
}

// ---------------------------------------------------------------------------------------------------------------------
void DoorController::setChoicePoints()
{
    addChoicePoint("Closed?", [this]()
    {
        return !doorState;
    });
    addChoicePoint("Is Locked?", [this]()
    {
        return lockState;
    });
}

// ---------------------------------------------------------------------------------------------------------------------
void DoorController::sendDoorLockChangedInd()
{
    auto doorLockChangedInd = prepareMessage<Control::DoorLockChangedInd>();
    doorLockChangedInd->doorId = doorId;
    doorLockChangedInd->locked = lockState;
    sendMessage(doorLockChangedInd);
}

// ---------------------------------------------------------------------------------------------------------------------
void DoorController::sendDoorStateChangedInd()
{
    auto doorSensorInd = prepareMessage<Control::DoorStateChangedInd>();
    doorSensorInd->doorId = doorId;
    doorSensorInd->open = doorState;
    sendMessage(doorSensorInd);
}
