#include <string>

#include "Administrator.h"
#include "Config.h"
#include "Admin.h"

// ---------------------------------------------------------------------------------------------------------------------
void Administrator::initialize()
{
    setSetting<std::shared_ptr<ConfigurationDatabase>>("Configuration Database", configurationDatabase);
    configurationDatabase->initDatabase();
}

// ---------------------------------------------------------------------------------------------------------------------
void Administrator::setStates()
{
    states =
    {
        "Idle",
        "Standby",
        "Retrieving",
        "Ready", "Storing",
        "Pending Events?"
    };
}

// ---------------------------------------------------------------------------------------------------------------------
void Administrator::setTransitions()
{
    addTransitionFunction<Config::InitializedInd>("Idle", "Standby", [this](const auto& message)
    {
        (void)this;
    });
    addTransitionFunction<Admin::BackendUrlReq>("Standby", "Retrieving", [this](const auto& message)
    {
        configurationDatabase->getBackendUrl();
    });
    addTransitionFunction<Config::BackendUrlInd>("Retrieving", "Ready", [this](const auto& message)
    {
        auto backEndUrlResp = prepareMessage<Admin::BackendUrlRsp>();
        backEndUrlResp->url = message.url;
        sendMessage(backEndUrlResp);
    });
    addTransitionFunction<Admin::DoorStateChangedInd>("Ready", "Storing", [this](const auto& message)
    {
        std::string event = "Door " + std::to_string(message.doorId) + " is " + (message.open ? "open" : "closed");
        configurationDatabase->storeEvent(event);
    });
    addTransitionFunction<Admin::DoorLockChangedInd>("Ready", "Storing", [this](const auto& message)
    {
        std::string event = "Door " + std::to_string(message.doorId )+ " is " + (message.locked ? "locked" : "unlocked");
        configurationDatabase->storeEvent(event);
    });
    addTransitionFunction<Admin::DoorStateChangedInd>("Storing", "Storing", [this](const auto& message)
    {
        std::string event = "Door " + std::to_string(message.doorId )+ " is " + (message.open ? "open" : "closed");
        pendingEvents.push_back(event);
    });
    addTransitionFunction<Admin::DoorLockChangedInd>("Storing", "Storing", [this](const auto& message)
    {
        std::string event = "Door " + std::to_string(message.doorId) + " is " + (message.locked ? "locked" : "unlocked");
        pendingEvents.push_back(event);
    });
    addTransitionFunction<Config::EventStoredInd>("Storing", "Pending Events?", [this](const auto& message)
    {
        (void)this;
    });
    addTransitionFunction<Logical::Yes>("Pending Events?", "Storing", [this](const auto& message)
    {
        std::string event = pendingEvents.front();
        pendingEvents.erase(pendingEvents.begin());
        configurationDatabase->storeEvent(event);
    });
    addTransitionFunction<Logical::No>("Pending Events?", "Ready", [this](const auto& message)
    {
        (void)this;
    });
}

// ---------------------------------------------------------------------------------------------------------------------
void Administrator::setChoicePoints()
{
    addChoicePoint("Pending Events?", [this]()
    {
        // Whether the pendingEvents vector contains any elements
        return !pendingEvents.empty();
    });
}
