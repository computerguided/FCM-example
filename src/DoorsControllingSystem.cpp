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
// Functional Components
// ---------------------------------------------------------------------------------------------------------------------
#include "Administrator.h"
#include "SystemController.h"
#include "DoorController.h"
            
// ---------------------------------------------------------------------------------------------------------------------
// Asynchronous Interface Handlers
// ---------------------------------------------------------------------------------------------------------------------
#include "BackendInterface.h"
#include "SensorHandler.h"
#include "ConfigurationDatabase.h"

// ---------------------------------------------------------------------------------------------------------------------
void DoorsControllingSystem::initialize()
{
    // -- Define the settings --
    settings["numDoors"] = std::any(numDoors);
    settings["openDoorTimeoutMs"] = std::any(FcmTime(30000)); // 30 seconds

    // -- Create asynchronous interface handlers --
    auto backendInterface = createComponent<BackendInterface>("Backend Interface", settings);
    auto sensorHandler = createComponent<SensorHandler>("Sensor Handler", settings);
    auto configurationDatabase = createComponent<ConfigurationDatabase>("Configuration Database", settings);

    // -- Create functional components --
    auto administrator = createComponent<Administrator>("Administrator", settings);
    auto systemController = createComponent<SystemController>("System Controller", settings);

    std::vector<std::shared_ptr<DoorController>> doorControllers;
    for (int i = 0; i < std::any_cast<uint>(settings["numDoors"]); i++)
    {
        auto doorController = createComponent<DoorController>("Door Controller[" + std::to_string(i) +"]", settings);
        doorControllers.push_back(doorController);
    }

    // -- Connect the interfaces of the handlers --
    connectInterface<Commands>(systemController, backendInterface);
    connectInterface<Config>(configurationDatabase, administrator);

    for (const auto& doorController : doorControllers)
    {
        connectInterface<Sensing>(sensorHandler, doorController);
    }

    // -- Connect functional components --
    connectInterface<Admin>(administrator, systemController);

    for (const auto& doorController : doorControllers)
    {
        connectInterface<Control>(doorController, systemController);
    }

    // -- Set log functions --
    for (const auto& component : components)
    {
        component->logTransitionFunction = logTransition;
        component->logDebugFunction = logDebug;
        component->logInfoFunction = logInfo;
        component->logWarningFunction = logWarning;
        component->logErrorFunction = logError;
    }

    // -- Initialize the components --
    initializeComponents();
}
