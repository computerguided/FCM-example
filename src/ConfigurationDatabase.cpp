#include "ConfigurationDatabase.h"

// ---------------------------------------------------------------------------------------------------------------------
// Interfaces
// ---------------------------------------------------------------------------------------------------------------------
#include "Config.h"

// ---------------------------------------------------------------------------------------------------------------------
void ConfigurationDatabase::initialize()
{
    // Nothing to do here
}

// ---------------------------------------------------------------------------------------------------------------------
void ConfigurationDatabase::initDatabase()
{
    // Mockup implementation:
    // - Reply with Config:InitializedInd

    FCM_PREPARE_MESSAGE(initializedInd, Config, InitializedInd);
    FCM_SEND_MESSAGE(initializedInd);
}

// ---------------------------------------------------------------------------------------------------------------------
void ConfigurationDatabase::getBackendUrl()
{
    // Mockup implementation:
    // - Reply with Admin:BackendUrlRsp

    FCM_PREPARE_MESSAGE(backendUrlInd, Config, BackendUrlInd);
    backendUrlInd->url = "http://backend.url";
    FCM_SEND_MESSAGE(backendUrlInd);
}

// ---------------------------------------------------------------------------------------------------------------------
void ConfigurationDatabase::storeEvent(const std::string& event)
{
    // Mockup implementation:
    // - Reply with Config:EventStoredInd
    // - Print the event to the console

    FCM_PREPARE_MESSAGE(eventStoredInd, Config, EventStoredInd);
    FCM_SEND_MESSAGE(eventStoredInd);

    logInfo("Event stored: " + event);
}
