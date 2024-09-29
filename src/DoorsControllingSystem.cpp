#include "DoorsControllingSystem.h"

// ---------------------------------------------------------------------------------------------------------------------
// Interfaces
// ---------------------------------------------------------------------------------------------------------------------
#include "Commands.h"

void DoorsControllingSystem::initialize()
{
    // Define the settings
    FcmSettings settings{};
    settings["numDoors"] = std::any(numDoors);
    settings["openDoorTimeoutMs"] = std::any(FcmTime(60000)); // 60 seconds

    // Create asynchronous interface handlers
    auto backendInterface = createComponent<BackendInterface>("Backend Interface");
    auto sensorHandler = createComponent<SensorHandler>("Sensor Handler", settings);
    auto configurationDatabase = createComponent<ConfigurationDatabase>("Configuration Database");

    // Create functional components
    auto administrator = createComponent<Administrator>("Administrator");
    auto systemController = createComponent<SystemController>("System Controller", settings);

    std::vector<std::shared_ptr<DoorController>> doorControllers;
    for (int i = 0; i < std::any_cast<uint>(settings["numDoors"]); i++)
    {
        auto doorController = createComponent<DoorController>("Door Controller[" + std::to_string(i) +"]", settings);
        doorControllers.push_back(doorController);
    }

    // Set references to handlers.
    systemController->setBackendInterface(backendInterface);
    administrator->setConfigurationDatabase(configurationDatabase);
    for (const auto& doorController : doorControllers)
    {
        doorController->setSensorHandler(sensorHandler);
    }

    // For testing
    backendInterface->setSensorHandler(sensorHandler);

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

    initializeComponents();

    // Set log functions
    for (const auto& component : components)
    {
        component->logTransitionFunction = logTransition;
        component->logDebugFunction = logDebug;
    }

    backendInterface->logInfoFunction = logInfo;
    configurationDatabase->logInfoFunction = logInfo;
}
