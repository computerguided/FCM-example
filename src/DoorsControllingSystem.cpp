#include "DoorsControllingSystem.h"

// ---------------------------------------------------------------------------------------------------------------------
// Interfaces
// ---------------------------------------------------------------------------------------------------------------------
#include "Commands.h"
#include "Config.h"
#include "Sensing.h"
#include "Control.h"
#include "Admin.h"

// ---------------------------------------------------------------------------------------------------------------------

void DoorsControllingSystem::initialize()
{
    // Define the settings
    FcmSettings settings{};
    settings["numDoors"] = std::any(numDoors);
    settings["openDoorTimeoutMs"] = std::any(FcmTime(30000)); // 30 seconds

    // Create asynchronous interface handlers
    auto backendInterface = createComponent<BackendInterface>("Backend Interface", settings);
    auto sensorHandler = createComponent<SensorHandler>("Sensor Handler", settings);
    auto configurationDatabase = createComponent<ConfigurationDatabase>("Configuration Database", settings);

    // Add handlers to the settings
    settings["backendInterface"] = std::any(backendInterface);
    settings["sensorHandler"] = std::any(sensorHandler);
    settings["configurationDatabase"] = std::any(configurationDatabase);

    // Create functional components
    auto administrator = createComponent<Administrator>("Administrator", settings);
    auto systemController = createComponent<SystemController>("System Controller", settings);

    std::vector<std::shared_ptr<DoorController>> doorControllers;
    for (int i = 0; i < std::any_cast<uint>(settings["numDoors"]); i++)
    {
        auto doorController = createComponent<DoorController>("Door Controller[" + std::to_string(i) +"]", settings);
        doorControllers.push_back(doorController);
    }

    // Connect the interfaces of the handlers
    FCM_CONNECT_INTERFACE(Commands, systemController, backendInterface);
    FCM_CONNECT_INTERFACE(Config, configurationDatabase, administrator);

    for (const auto& doorController : doorControllers)
    {
        FCM_CONNECT_INTERFACE(Sensing, sensorHandler, doorController);
    }

    // Connect functional components.
    FCM_CONNECT_INTERFACE(Admin, administrator, systemController);
    for (const auto& doorController : doorControllers)
    {
        FCM_CONNECT_INTERFACE(Control, doorController, systemController);
    }

    // Set log functions
    for (const auto& component : components)
    {
        component->logTransitionFunction = logTransition;
        component->logDebugFunction = logDebug;
        component->logInfoFunction = logInfo;
        component->logWarningFunction = logWarning;
        component->logErrorFunction = logError;
    }

    initializeComponents();
}
