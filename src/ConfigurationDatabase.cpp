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

    auto initializedInd = prepareMessage<Config::InitializedInd>();
    sendMessage(initializedInd);
}

// ---------------------------------------------------------------------------------------------------------------------
void ConfigurationDatabase::getBackendUrl()
{
    // Mockup implementation:
    // - Reply with Admin:BackendUrlRsp

    auto backendUrlInd = prepareMessage<Config::BackendUrlInd>();
    backendUrlInd->url = "http://backend.url";
    sendMessage(backendUrlInd);
}

// ---------------------------------------------------------------------------------------------------------------------
void ConfigurationDatabase::storeEvent(const std::string& event)
{
    // Mockup implementation:
    // - Reply with Config:EventStoredInd
    // - Print the event to the console

    auto eventStoredInd = prepareMessage<Config::EventStoredInd>();
    sendMessage(eventStoredInd);

    logInfo("Event stored: " + event);
}
