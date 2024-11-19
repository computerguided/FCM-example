#include <iostream>
#include <thread>
#include <string>

#include "BackendInterface.h"

// ---------------------------------------------------------------------------------------------------------------------
// Interfaces
// ---------------------------------------------------------------------------------------------------------------------
#include "Commands.h"


// ---------------------------------------------------------------------------------------------------------------------
void BackendInterface::initialize()
{
    setSetting<std::shared_ptr<SensorHandler>>("sensorHandler", sensorHandler);
    commandLineThread = std::thread(&BackendInterface::commandLineInput, this);
}

// ---------------------------------------------------------------------------------------------------------------------
void BackendInterface::connect(const std::string& url)
{
    logInfo("Connecting to backend at " + url);

    // Mockup implementation:
    // - Reply with Commands:ConnectedInd
    // - Send a single KeepAliveInd message

    FCM_PREPARE_MESSAGE(connectedInd, Commands, ConnectedInd);
    FCM_SEND_MESSAGE(connectedInd);

    FCM_PREPARE_MESSAGE(keepAliveInd, Commands, KeepAliveInd);
    FCM_SEND_MESSAGE(keepAliveInd);
}

// ---------------------------------------------------------------------------------------------------------------------
void BackendInterface::commandLineInput()
{
    std::string input;
    while (true) {
        std::getline(std::cin, input);

        // Possible commands:
        // -AddTag <doorId> <tagId>
        // -RemoveTag <doorId> <tagId>
        // -LockDoor <doorId>
        // -UnlockDoor <doorId>
        // -OpenDoor <doorId>
        // -CloseDoor <doorId>
        // -Exit

        // Parse the input.
        // - If the command is recognized, prepare the corresponding message and send it.
        // - If the command is not recognized, print an error message.

        // Get the command and the parameters.
        std::string command;
        uint doorId{};
        uint tagId{};
        size_t spacePos = input.find(' ');

        if (spacePos == std::string::npos)
        {
            executeCommand(input);
            continue;
        }

        command = input.substr(0, spacePos);
        size_t spacePos2 = input.find(' ', spacePos + 1);

        try
        {
            if (spacePos2 == std::string::npos)
            {
                doorId = std::stoi(input.substr(spacePos + 1));
                executeCommand(command, doorId);
                continue;
            }

            doorId = std::stoi(input.substr(spacePos + 1, spacePos2 - spacePos - 1));
            tagId = std::stoi(input.substr(spacePos2 + 1));
            executeCommand(command, doorId, tagId);
        }
        catch (std::invalid_argument& e)
        {
            std::cout << "ERROR - Invalid argument(s)!" << std::endl;
            continue;
        }
    }
}

// ---------------------------------------------------------------------------------------------------------------------
void BackendInterface::executeCommand(const std::string &command, const uint doorId, const uint tagId)
{
    if (command == "AddTag")
    {
        FCM_PREPARE_MESSAGE(addTagInd, Commands, AddTagInd);
        addTagInd->doorId = doorId;
        addTagInd->tagId = tagId;
        FCM_SEND_MESSAGE(addTagInd);
    }
    else if (command == "RemoveTag")
    {
        FCM_PREPARE_MESSAGE(removeTagInd, Commands, RemoveTagInd);
        removeTagInd->doorId = doorId;
        removeTagInd->tagId = tagId;
        FCM_SEND_MESSAGE(removeTagInd);
    }
    else if (command == "LockDoor")
    {
        FCM_PREPARE_MESSAGE(lockDoorInd, Commands, LockDoorInd);
        lockDoorInd->doorId = doorId;
        FCM_SEND_MESSAGE(lockDoorInd);
    }
    else if (command == "UnlockDoor")
    {
        FCM_PREPARE_MESSAGE(unlockDoorInd, Commands, UnlockDoorInd);
        unlockDoorInd->doorId = doorId;
        FCM_SEND_MESSAGE(unlockDoorInd);
    }
    else if (command == "OpenDoor")
    {
        sensorHandler->sendDoorSensorInd(doorId, true);
    }
    else if (command == "CloseDoor")
    {
        sensorHandler->sendDoorSensorInd(doorId, false);
    }
    else if (command == "Exit")
    {
        exit(0);
    }
    else
    {
        std::cout << "Unknown command: " << command << std::endl;
    }
}
