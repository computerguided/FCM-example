#include <string>

#include "Administrator.h"
#include "Config.h"
#include "Admin.h"

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
    addTransitionFunction<Config::InitializedInd>("Idle", "Standby",
        [](const auto& message){}
    );
    addTransitionFunction<Admin::BackendUrlReq>("Standby", "Retrieving",
        [this](const auto& message)
        {
            configurationDatabase->getBackendUrl();
        }
    );
    addTransitionFunction<Config::BackendUrlInd>("Retrieving", "Ready",
        [this](const auto& message)
        {
            FCM_PREPARE_MESSAGE(backEndUrlResp, Admin, BackendUrlRsp);
            backEndUrlResp->url = message.url;
            FCM_SEND_MESSAGE(backEndUrlResp);
        }
    );
    FCM_ADD_TRANSITION("Ready", Admin, DoorStateChangedInd, "Storing",
        std::string event = "Door " + std::to_string(message.doorId) + " is " + (message.open ? "open" : "closed");
        configurationDatabase->storeEvent(event);
    );
    FCM_ADD_TRANSITION("Ready", Admin, DoorLockChangedInd, "Storing",
        std::string event = "Door " + std::to_string(message.doorId )+ " is " + (message.locked ? "locked" : "unlocked");
        configurationDatabase->storeEvent(event);
    );
    FCM_ADD_TRANSITION("Storing", Admin, DoorStateChangedInd, "Storing",
        std::string event = "Door " + std::to_string(message.doorId )+ " is " + (message.open ? "open" : "closed");
        pendingEvents.push_back(event);
    );
    FCM_ADD_TRANSITION("Storing", Admin, DoorLockChangedInd, "Storing",
        std::string event = "Door " + std::to_string(message.doorId) + " is " + (message.locked ? "locked" : "unlocked");
        pendingEvents.push_back(event);
    );
    FCM_ADD_TRANSITION("Storing", Config, EventStoredInd, "Pending Events?",
        // NOP
    );
    FCM_ADD_TRANSITION("Pending Events?", Logical, Yes, "Storing",
        std::string event = pendingEvents.front();
        pendingEvents.erase(pendingEvents.begin());
        configurationDatabase->storeEvent(event);
    );
    FCM_ADD_TRANSITION("Pending Events?", Logical, No, "Ready",
        // NOP
    );
}

// ---------------------------------------------------------------------------------------------------------------------
void Administrator::setChoicePoints()
{
    FCM_ADD_CHOICE_POINT("Pending Events?",
        // Whether the pendingEvents vector contains any elements
        return !pendingEvents.empty();
    );
}

// ---------------------------------------------------------------------------------------------------------------------
void Administrator::initialize()
{
    FcmFunctionalComponent::initialize();
    configurationDatabase->initDatabase();
}
