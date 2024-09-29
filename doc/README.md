# System specification

## Description

The Doors Controlling System (DCS) is designed to manage access control by monitoring and controlling door locks. It comprises several components including doors with sensors, a central controller, a backend system, and a database. The system supports both administrative and guest operations, ensuring secure and controlled access.

## System architecture

The overall system architecture which identifies all the actors is given in the figure below.

![](https://www.plantuml.com/plantuml/img/PL7BJiGm3BpxAwpUS-760MaN46Yb5HU-m4tCgceQhv9KlCI_uoHj5oqtspEUZ2Uxb2dcUVAGnY6SATA4LgQp10xvDNzwniWsKpXv_aFv1iH3o1pVoFAJA7NuOhp3M_W12E8OdKXC3uf4yPuZKiBkqdQDr9CTERWAthUw0t2KgQUa6dr57fTU8R9PLCjDGwZGlbH3of5qhlZc5My-r6IZdsPEkTAVIzLT33PvAQlgstgP7GRExnB72XttBzqo7igrYjNvOMcAsI9ZrYqzVbatvZe2vVRuVteTbDcUWkrDioO5q8vfCW1hWAPb0h3JJd_p5m00)

The description of each one of the involved actors is given in the following table.

<table>
  <tr>
   <td>Actor
   </td>
   <td>Description
   </td>
  </tr>
  <tr>
   <td>Door
   </td>
   <td>Equipped with sensors to detect its status (open or closed) and its lock state (locked or unlocked). It maintains an internal list of tags that can be used to operate it. The Door communicates with the Controller to report its status and respond to commands such as locking or unlocking.
   </td>
  </tr>
  <tr>
   <td>Controller
   </td>
   <td>Responsible for coordinating the overall system. It manages the state of the doors and interfaces with the backend. It handles commands from the backend, such as locking/unlocking doors and adding/removing tags, and communicates with the Door to execute these commands.
   </td>
  </tr>
  <tr>
   <td>Database
   </td>
   <td>Stores configuration settings, event data, and system history. It is initialized by the Administrator and accessed by the Controller and Backend to store and retrieve necessary information for system operations.
   </td>
  </tr>
  <tr>
   <td>Backend
   </td>
   <td>Facilitate remote operations and management. It communicates changes in door states, lock states, and alarms, and handles error messages. It interacts with the Controller and the Administrator to ensure secure and efficient access control.
   </td>
  </tr>
  <tr>
   <td>Administrator
   </td>
   <td>Responsible for initializing the system database, managing system settings, and storing events. The Administrator ensures that the system is correctly configured and maintains the history of events by interacting with the Database and other components.
   </td>
  </tr>
  <tr>
   <td>Guest
   </td>
   <td>Interacts with the system to gain access through doors. The system detects actions performed by the Guest, such as opening, closing, locking, or unlocking doors. The Guest's actions are monitored and processed by the Door and Controller to ensure proper access control.
   </td>
  </tr>
</table>

# Use cases

In the table below all the identified use cases are listed.

<table>
  <tr>
   <td>Use case
   </td>
   <td>Objective
   </td>
   <td>Actors
   </td>
  </tr>
  <tr>
   <td>Door detected
   </td>
   <td>A connected Door is detected.
   </td>
   <td>
<ul>

<li>Door

<li>Controller
</li>
</ul>
   </td>
  </tr>
  <tr>
   <td>Get door state
   </td>
   <td>The Door is queried for its state and returned it.
   </td>
   <td>
<ul>

<li>Door

<li>Controller

<li>Backend

<li>Database
</li>
</ul>
   </td>
  </tr>
  <tr>
   <td>Guest closed door
   </td>
   <td>The detection that the Guest closed the Door was processed.
   </td>
   <td rowspan="4" >
<ul>

<li>Door

<li>Controller

<li>Database

<li>Backend

<li>Guest
</li>
</ul>
   </td>
  </tr>
  <tr>
   <td>Guest opened door
   </td>
   <td>The detection that the Guest opened the Door was processed.
   </td>
  </tr>
  <tr>
   <td>Guest locked door
   </td>
   <td>The detection that the Guest locked the Door was processed.
   </td>
  </tr>
  <tr>
   <td>Guest unlocked door
   </td>
   <td>The detection that the Guest unlocked the Door was processed.
   </td>
  </tr>
  <tr>
   <td>Administrator locks door
   </td>
   <td>The Door is remotely locked by the Administrator using the Backend.
   </td>
   <td rowspan="4" >
<ul>

<li>Door

<li>Controller

<li>Database

<li>Backend

<li>Administrator
</li>
</ul>
   </td>
  </tr>
  <tr>
   <td>Administrator unlocks door
   </td>
   <td>The Door is remotely unlocked by the Administrator using the Backend.
   </td>
  </tr>
  <tr>
   <td>Tag added to Door
   </td>
   <td>A tag is added to the Door by the Administrator using the Backend.
   </td>
  </tr>
  <tr>
   <td>Tag removed from Door
   </td>
   <td>A tag is removed from the Door by the Administrator using the Backend.
   </td>
  </tr>
</table>

# Controller Functional decomposition
_The functional decomposition for the DCS Controller is performed in this chapter._

---

## Functionality

The Doors Controlling System (DCS) Controller is responsible for managing the overall operation of the DCS by coordinating the activities of various components, ensuring secure and efficient access control. The functionality of the Controller can be broken down into the following key areas:

1. Door State Management
    * Detection: The Controller detects the connection and disconnection of doors via sensors.
    * State Query: The Controller queries the state of each door (open/closed, locked/unlocked) and updates its internal state accordingly.
    * State Monitoring: Continuous monitoring of door states to ensure they are correctly reported and handled.
2. Command Handling
    * Lock/Unlock Commands: The Controller receives commands from the backend to lock or unlock doors and executes these commands by interfacing with the Door Controllers.
    * Tag Management: Commands to add or remove tags (access credentials) to/from doors are processed by the Controller and forwarded to the appropriate Door Controller.
    * Remote Operations: The Controller facilitates remote operations, allowing the Administrator to manage doors via the backend.
3. Event Processing
    * State Change Events: The Controller processes events related to changes in door states, such as doors being opened or closed, and locks being engaged or disengaged.
    * Error and Alarm Handling: The Controller manages error messages and alarm signals from doors, ensuring that any issues are promptly reported and handled.
4. Interface Management
    * Backend Interface: The Controller maintains a connection to the backend server, communicating changes in door states, lock states, and alarms. It handles error messages from the backend and ensures synchronization between the backend and the doors.
    * Database Interface: The Controller interacts with the configuration database to store and retrieve settings and event data, ensuring that the system’s history and configuration are accurately maintained.
5. System Initialization and Configuration
    * Initialization: During startup, the Controller initializes the system by detecting all doors, retrieving necessary configuration settings, and establishing connections with the backend and other components.
    * Configuration Management: The Controller handles the configuration settings, such as initializing the database, retrieving backend URLs, and storing system events.
6. Administrative Functions
    * Database Management: The Controller assists the Administrator in initializing the database, managing system settings, and storing events.
    * Access Control: It ensures that only authorized tags are allowed to operate the doors, maintaining a secure access control environment.

By integrating these functionalities, the DCS Controller ensures secure and efficient operation of the Doors Controlling System, providing a robust solution for access control and monitoring in various environments.

This comprehensive approach allows the DCS Controller to effectively manage the various aspects of door control, ensuring a secure, reliable, and user-friendly access control system.

## Functional decomposition

The result of the functional decomposition is given in the functional component diagram in the figure below.

![](https://www.plantuml.com/plantuml/img/RLF1JiCm3BtdAwASjaDxu0OQqs0JWlEE5A6iTQTehJCbcSH0_3jEqgNfngtsUtwsdzELTTAuKzynUr1ub4RslDRzKIEWsxfp1zn0xIJkEyWeFuppDtHWMbd3YoQg-WR-oE_PBsEfdfJG6TrrOBYqN6pFra5VuJgbHKQMJQzGMMUaqv7_b6S4OwWRu1RGQlCgiKco8LFXa1EHjvFr0R19KmRgSqnMcD83coPjrJvmrk7pH4sLnWetqicTj4HaixdtfgSszbEr0pd6meDXWmiIXXUnnWkE5JuYjUGhl_iYGydHoFNMP6GVld-82Flb5IQjRGmzJFXePQC71pVQ6vFx7NZfAaMHTHmXhry45SyFQeiYQ-wpqpiK4_WQNPHbLAFNSNENC4DozHRtnUF8uNcb4nGTjAvOJl3fEoBrorbOldWe724sF81eI3pNbT8YXovyFzo4zi-2PRcyykE1pnnOHsvL6Doblz31d36seahw6_y0)

The responsibility for each one of the identified Functional Components is given in the following table.

<table>
  <tr>
   <td>Functional Component
   </td>
   <td>Responsibility
   </td>
  </tr>
  <tr>
   <td>Administrator
   </td>
   <td>
<ul>

<li>Initialize the database.

<li>Read information from the database.

<li>Store information into the database.
</li>
</ul>
   </td>
  </tr>
  <tr>
   <td>System Controller
   </td>
   <td>
<ul>

<li>Coordinate the overall system, manage door states, and interface with the backend.

<li>Handle commands from the backend such as locking/unlocking doors, and adding/removing tags.
</li>
</ul>
   </td>
  </tr>
  <tr>
   <td>Door Controller
   </td>
   <td>
<ul>

<li>Monitor and control the state and lock of the door.

<li>Handle sensor data and ensure correct responses to door events (e.g., opening, closing, locking).
</li>
</ul>
   </td>
  </tr>
</table>

The responsibility and the function interface for each one of the identified Asynchronous Interface Handlers is given in the table below.

<table>
  <tr>
   <td>Async Interface Handler
   </td>
   <td>Responsibility
   </td>
   <td>Functions
   </td>
  </tr>
  <tr>
   <td>Backend Interface
   </td>
   <td>
<ul>

<li>Connect to the backend server.

<li>Communicate changes in door lock states, door states, and alarms.

<li>Handle error messages.
</li>
</ul>
   </td>
   <td>
<ul>

<li><code>connect(url)</code>

<li><code>doorLockChanged(doorId, locked)</code>

<li><code>doorStateChanged(doorId, open)</code>

<li><code>alarm(doorId, alarm)</code>

<li><code>error(doorId, error)</code>
</li>
</ul>
   </td>
  </tr>
  <tr>
   <td>Configuration Database
   </td>
   <td>
<ul>

<li>Initialize and manage configuration settings.

<li>Store and retrieve event data.
</li>
</ul>
   </td>
   <td>
<ul>

<li><code>initDatabase()</code>

<li><code>getBackendUrl()</code>

<li><code>storeEvent(event)</code>
</li>
</ul>
   </td>
  </tr>
  <tr>
   <td>Sensor Handler
   </td>
   <td>
<ul>

<li>Manage door and lock sensors.

<li>Execute lock/unlock commands.

<li>Add and remove tags.
</li>
</ul>
   </td>
   <td>
<ul>

<li><code>enableLockSensor(doorId)</code>

<li><code>enableDoorSensor(doorId)</code>

<li><code>lock(doorId)</code>

<li><code>unlock(doorId)</code>

<li><code>addTag(doorId, tagId)</code>

<li><code>removeTag(doorId, tagId)</code>
</li>
</ul>
   </td>
  </tr>
</table>



# Interfaces

## Purpose

The identified interfaces and their purpose are given in the following table.

<table>
  <tr>
   <td>Interface
   </td>
   <td>Purpose
   </td>
  </tr>
  <tr>
   <td>commands
   </td>
   <td>Facilitates communication between the backend and the system controller, enabling actions such as locking/unlocking doors and managing tags.
   </td>
  </tr>
  <tr>
   <td>Config
   </td>
   <td>Manages configuration settings for the system, including initialization and retrieval of settings from the configuration database.
   </td>
  </tr>
  <tr>
   <td>Admin
   </td>
   <td>Handles administrative tasks such as system initialization, retrieving backend URLs, and storing events in the database.
   </td>
  </tr>
  <tr>
   <td>Control
   </td>
   <td>Manages the interaction between the system controller and door controllers, including monitoring door states and executing lock/unlock commands.
   </td>
  </tr>
  <tr>
   <td>Sensing
   </td>
   <td>Manages and conveys the status of door-related sensors and is responsible for detecting and reporting changes in the state of door sensors and lock sensors.
   </td>
  </tr>
</table>

## “Commands” interface

The messages and their parameters for the “Commands” interface are given in the following table.

<table>
  <tr>
   <td>Message
   </td>
   <td>Description 
   </td>
   <td>Parameter
   </td>
   <td>Type
   </td>
  </tr>
  <tr>
   <td><code>ConnectedInd</code>
   </td>
   <td>Indicates a successful connection.
   </td>
   <td><code>-</code>
   </td>
   <td><code>-</code>
   </td>
  </tr>
  <tr>
   <td><code>LockDoorInd</code>
   </td>
   <td>Commands to lock a specific door.
   </td>
   <td><code>doorId</code>
   </td>
   <td><code>uint</code>
   </td>
  </tr>
  <tr>
   <td><code>UnlockDoorInd</code>
   </td>
   <td>Commands to unlock a specific door.
   </td>
   <td><code>doorId</code>
   </td>
   <td><code>uint</code>
   </td>
  </tr>
  <tr>
   <td><code>AddTagInd</code>
   </td>
   <td>Commands to add a tag to a door.
   </td>
   <td><code>tagId</code>
   </td>
   <td><code>uint</code>
   </td>
  </tr>
  <tr>
   <td><code>RemoveTagInd</code>
   </td>
   <td>Commands to remove a tag from a door.
   </td>
   <td><code>tagId</code>
   </td>
   <td><code>uint</code>
   </td>
  </tr>
</table>

## “Config” interface

The messages and their parameters for the “Config” interface are given in the following table.

<table>
  <tr>
   <td>Message
   </td>
   <td>Description 
   </td>
   <td>Parameter
   </td>
   <td>Type
   </td>
  </tr>
  <tr>
   <td><code>BackendUrlInd</code>
   </td>
   <td>Provides the URL for the backend.
   </td>
   <td><code>url</code>
   </td>
   <td><code>string</code>
   </td>
  </tr>
  <tr>
   <td><code>EventStoredInd</code>
   </td>
   <td>Indicates that an event has been stored.
   </td>
   <td><code>-</code>
   </td>
   <td><code>-</code>
   </td>
  </tr>
</table>

## “Admin” interface

The messages and their parameters for the “Admin” interface are given in the following table.

<table>
  <tr>
   <td>Message
   </td>
   <td>Description 
   </td>
   <td>Parameter
   </td>
   <td>Type
   </td>
  </tr>
  <tr>
   <td><code>BackendUrlReq</code>
   </td>
   <td>Requests the backend URL.
   </td>
   <td><code>-</code>
   </td>
   <td><code>-</code>
   </td>
  </tr>
  <tr>
   <td><code>BackendUrlRsp</code>
   </td>
   <td>Responds with the backend URL.
   </td>
   <td><code>url</code>
   </td>
   <td><code>string</code>
   </td>
  </tr>
  <tr>
   <td rowspan="2" ><code>DoorStateChangedInd</code>
   </td>
   <td rowspan="2" >Indicates a change in the state of a door.
   </td>
   <td><code>doorId</code>
   </td>
   <td><code>uint</code>
   </td>
  </tr>
  <tr>
   <td><code>open</code>
   </td>
   <td><code>bool</code>
   </td>
  </tr>
  <tr>
   <td rowspan="2" ><code>DoorLockChangedInd</code>
   </td>
   <td rowspan="2" >Indicates a change in the lock state of a door
   </td>
   <td><code>doorId</code>
   </td>
   <td><code>uint</code>
   </td>
  </tr>
  <tr>
   <td><code>locked</code>
   </td>
   <td><code>bool</code>
   </td>
  </tr>
</table>

## “Control” interface

The messages and their parameters for the “Control” interface are given in the following table.

<table>
  <tr>
   <td>Message
   </td>
   <td>Description 
   </td>
   <td>Parameter
   </td>
   <td>Type
   </td>
  </tr>
  <tr>
   <td><code>DoorDetectedInd</code>
   </td>
   <td>Indicates that a door has been detected.
   </td>
   <td><code>doorId</code>
   </td>
   <td><code>uint</code>
   </td>
  </tr>
  <tr>
   <td><code>ReleaseDoorInd</code>
   </td>
   <td>Commands to release a door for operation.
   </td>
   <td><code>-</code>
   </td>
   <td><code>-</code>
   </td>
  </tr>
  <tr>
   <td><code>SetLockInd</code>
   </td>
   <td>Commands to set the lock state of a door.
   </td>
   <td><code>locked</code>
   </td>
   <td><code>bool</code>
   </td>
  </tr>
  <tr>
   <td rowspan="2" ><code>DoorStateChangedInd</code>
   </td>
   <td rowspan="2" >Indicates a change in the door state.
   </td>
   <td><code>doorId</code>
   </td>
   <td><code>uint</code>
   </td>
  </tr>
  <tr>
   <td><code>open</code>
   </td>
   <td><code>bool</code>
   </td>
  </tr>
  <tr>
   <td rowspan="3" ><code>DoorLockChangedInd</code>
   </td>
   <td rowspan="3" >Indicates a change in the lock state.
   </td>
   <td><code>doorId</code>
   </td>
   <td><code>uint</code>
   </td>
  </tr>
  <tr>
   <td><code>tagId</code>
   </td>
   <td><code>uint</code>
   </td>
  </tr>
  <tr>
   <td><code>locked</code>
   </td>
   <td><code>bool</code>
   </td>
  </tr>
  <tr>
   <td><code>AddTagInd</code>
   </td>
   <td>Commands to add a tag to a door.
   </td>
   <td><code>tagId</code>
   </td>
   <td><code>uint</code>
   </td>
  </tr>
  <tr>
   <td><code>RemoveTagInd</code>
   </td>
   <td>Commands to remove a tag from a door.
   </td>
   <td><code>tagId</code>
   </td>
   <td><code>uint</code>
   </td>
  </tr>
  <tr>
   <td rowspan="2" ><code>ErrorInd</code>
   </td>
   <td rowspan="2" >Indicates an error related to a door.
   </td>
   <td><code>doorId</code>
   </td>
   <td><code>uint</code>
   </td>
  </tr>
  <tr>
   <td><code>error</code>
   </td>
   <td><code>string</code>
   </td>
  </tr>
  <tr>
   <td rowspan="2" ><code>AlarmInd</code>
   </td>
   <td rowspan="2" >Indicates an alarm condition related to a door.
   </td>
   <td><code>doorId</code>
   </td>
   <td><code>uint</code>
   </td>
  </tr>
  <tr>
   <td><code>alarm</code>
   </td>
   <td><code>string</code>
   </td>
  </tr>
</table>

## “Sensing” interface

The messages and their parameters for the “Sensing” interface are given in the following table.

<table>
  <tr>
   <td>Message
   </td>
   <td>Description 
   </td>
   <td>Parameter
   </td>
   <td>Type
   </td>
  </tr>
  <tr>
   <td><code>DoorDetectedInd</code>
   </td>
   <td>Indicates that a door has been detected.
   </td>
   <td><code>doorId</code>
   </td>
   <td><code>uint</code>
   </td>
  </tr>
  <tr>
   <td><code>LockSensorInd</code>
   </td>
   <td>Indicates the status of the lock sensor.
   </td>
   <td><code>locked</code>
   </td>
   <td><code>bool</code>
   </td>
  </tr>
  <tr>
   <td><code>DoorSensorInd</code>
   </td>
   <td>Indicates the status of the door sensor.
   </td>
   <td><code>open</code>
   </td>
   <td><code>bool</code>
   </td>
  </tr>
  <tr>
   <td><code>LockFailInd</code>
   </td>
   <td>Indicates a failure in the lock mechanism.
   </td>
   <td><code>-</code>
   </td>
   <td><code>-</code>
   </td>
  </tr>
</table>

# Backend Interface

_The Backend Interface is responsible for handling the connection to the backend server and communicates the changes in door lock states, door states, and alarms. In this example the component is stubbed to allow for manual testing via the command line._

---

## Context

The context of the Backend Interface is given in the figure below. Note that the reference to the Sensor Handler is only necessary for testing the functionality of detecting the opening and closing of a door, i.e. mimicking the signal of the door sensor.

![](https://www.plantuml.com/plantuml/img/PP712i8m44Jl-nLBJtfexueMiI1wzbgGs6wbDDb8iXvK_7TZBQ7QOsRUJ1XsuqKvkHaDlclvgfmoM5bpjKmiHxbhGaULABve6Y5FG3oma6jKHJiRqFP1kCO5l01YFZInEAirELGUa-FT2vcIYoWd06nhGa_ihTihhYFRAoKFMlBbpghgYEluTOzklsB9KGwri_bdXmbfVsgRdYk6Tt0dFMawngV-Aij6Q_gDiJlLr4YQ__YJWYpB_rOkSIRafULBoRMr3iCfXEO0cn0C5ta3)

## Initialization

To allow for manual testing, in this example the Backend Interface implements a command line interface in a separate thread. This is done in the overridden `initialize()` method where an instantiate of `std::thread` is created and stored in the `commandLineThread` attribute.

```cpp
commandLineThread = std::thread(&BackendInterface::commandLineInput, this);
```

The parameter of `std::thread constructor` is a callable object, which is the `commandLineInput()` method discussed in the next section.

## Command line input

For testing, a very simple command line interface is defined in which the following commands are supported:

* `AddTag <doorId> <tagId>`
* `RemoveTag <doorId> <tagId>`
* `LockDoor <doorId>`
* `UnlockDoor <doorId>`
* `OpenDoor <doorId>`
* `CloseDoor <doorId>`
* `Exit`

To store the command, first a local variable is defined.

```cpp
std::string input;
```

Because the function is called in the created thread (see previous section), a while-loop can be created that runs indefinitely.

```cpp
while (true)
{
    // ...get the input from the command line, parse it and execute the command...
}
```

The first step is to get the input from the command line, i.e. `std::cin` and store it in the `input` variable.

```cpp
std::getline(std::cin, input);
```

This is a blocking call, which is not a problem because this function will be running inside a separate thread.

Since the input will have a maximum of 3 parameters, these can be defined.

```cpp
std::string command;
std::string doorId;
std::string tagId;
```

Because the parameters in the input will be separated by spaces, the first step in extracting the parameter is finding the position of the first space by calling the `std::string::find()` method.

```cpp
size_t spacePos = input.find(' ');
```

When the space is _not_ found, the `std::string::npos` is returned. This is the case when the input comprises a command with no parameters, e.g. “Exit”. As such the input can be offered as the argument in calling the `executeCommand()` method and the next input can be awaited.

```cpp
if (spacePos == std::string::npos)
{
    executeCommand(input);
    continue;
}
```

If the first space is found, then the `command` is the string before this space.

```cpp
command = input.substr(0, spacePos);
```

The next step is to find the second space in the remainder of the string to retrieve the parameters.

```cpp
size_t spacePos2 = input.find(' ', spacePos + 1);
```

To capture entering a command with invalid parameters, e.g. conversion to integers fails, an error is captured.

```cpp
try 
{
    // ...parse to get the parameters...
}
catch (std::invalid_argument& e)
{
    std::cout << "ERROR - Invalid argument(s)!" << std::endl;
    continue;
}
```

If the second space is not found, there is no secondary parameter and the `doorId` can be set and the command executed.

```cpp
if (spacePos2 == std::string::npos)
{
    doorId = std::stoi(input.substr(spacePos + 1));
    executeCommand(command, doorId);
    continue;
}
```

When the second space is found,  then the `tagId` can also be set next to the `doorId`, and the command can be executed.

```cpp
doorId = std::stoi(input.substr(spacePos + 1, spacePos2 - spacePos - 1));
tagId = std::stoi(input.substr(spacePos2 + 1));
executeCommand(command, doorId, tagId);
```

## Execute command

To execute the parsed command line input, the `executeCommand()` method must be  called.

```cpp
executeCommand(const std::string& command, const uint doorId = 0, const uint tagId = 0);
```

The format is to define the operation to be performed based on the value of the command parameter.

```cpp
if (command == "AddTag")
{
    // ...Send message Commands:AddTagInd...
}
else if (command == "RemoveTag")
{
    // ...Send message Commands:RemoveTagInd...
}
else if (command == "LockDoor")
{
    // ...Send message Commands:LockDoorInd...
}
else if (command == "UnlockDoor")
{
    // ...Send message Commands:UnlockDoorInd...
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
```

Note that for the “OpenDoor” and “CloseDoor” commands we use the reference to the Sensor Handler which is required in order to test this functionality.

## Functions overview

The functions interface of the Backend Interface handler is given in the following table.

<table>
  <tr>
   <td>Name
   </td>
   <td>Description
   </td>
   <td>Parameter
   </td>
   <td>Type
   </td>
  </tr>
  <tr>
   <td><code>connect</code>
   </td>
   <td>Start the connection process to the backend server.
   </td>
   <td><code>url</code>
   </td>
   <td><code>string</code>
   </td>
  </tr>
  <tr>
   <td rowspan="2" ><code>doorLockChanged</code>
   </td>
   <td rowspan="2" >Inform the backend that the status of the door lock changed.
   </td>
   <td><code>doorId</code>
   </td>
   <td><code>int</code>
   </td>
  </tr>
  <tr>
   <td><code>locked</code>
   </td>
   <td><code>bool</code>
   </td>
  </tr>
  <tr>
   <td rowspan="2" ><code>doorStateChanged</code>
   </td>
   <td rowspan="2" >Inform the backend that the state of the door changed.
   </td>
   <td><code>doorId</code>
   </td>
   <td><code>int</code>
   </td>
  </tr>
  <tr>
   <td><code>open</code>
   </td>
   <td><code>bool</code>
   </td>
  </tr>
  <tr>
   <td rowspan="2" ><code>alarm</code>
   </td>
   <td rowspan="2" >Inform the backend about an alarm that was generated for the specified door.
   </td>
   <td><code>doorId</code>
   </td>
   <td><code>int</code>
   </td>
  </tr>
  <tr>
   <td><code>alarm</code>
   </td>
   <td><code>string</code>
   </td>
  </tr>
  <tr>
   <td rowspan="2" ><code>error</code>
   </td>
   <td rowspan="2" >Inform the backend that an error occurred with the specified door.
   </td>
   <td><code>doorId</code>
   </td>
   <td><code>int</code>
   </td>
  </tr>
  <tr>
   <td><code>error</code>
   </td>
   <td><code>string</code>
   </td>
  </tr>
</table>

For this test application, these functions are stubbed.

# Configuration Database
_The Configuration Database is responsible for handling the connection with the database._

---

## Context

The context of the Configuration Database handler is given in the figure below.


![](https://www.plantuml.com/plantuml/img/LP2n2i9038RtF4Nef4Ex2nKgYk3iAaXiqtBOovMxT53ntJrArUiMydq_VqWLbBoEjeTmDpAG9ukriuCJ5ZthesVqN2j9rtEYl03n9Cg-fPgFBghcoRZ53Rm1VdcanXenGJsfyqW1irswoG34DHmBfJNTnFVJE4Pid5paG4et2XpDrNhshgPDr4XWpkVvtu1bTPcYhryMnV92W8gbYS_u0000)

## Functions overview

The functions interface of the Configuration Database handler is given in the following table.

<table>
  <tr>
   <td>Name
   </td>
   <td>Description
   </td>
   <td>Parameter
   </td>
   <td>Type
   </td>
  </tr>
  <tr>
   <td><code>initDatabase</code>
   </td>
   <td>Create the connection with the database.
   </td>
   <td><code>-</code>
   </td>
   <td><code>-</code>
   </td>
  </tr>
  <tr>
   <td><code>getBackendUrl</code>
   </td>
   <td>Return the URL of the backend.
   </td>
   <td><code>-</code>
   </td>
   <td><code>-</code>
   </td>
  </tr>
  <tr>
   <td><code>storeEvent</code>
   </td>
   <td>Store the event in the database.
   </td>
   <td><code>event</code>
   </td>
   <td><code>std::string</code>
   </td>
  </tr>
</table>

For this test application, these functions are stubbed and immediately send the expected reply.

# Sensor Handler
_The Sensor Handler is responsible for handling the interface to the doors and their sensors._

---

## Context

The context of the Sensor Handler is given in the figure below.

![](https://www.plantuml.com/plantuml/img/NP3D2i8m48JlUOgb9ptemPjGeQ28ddjKaT1iIp3TBKa4V_3TJL8fhSUTcVsOtS9vQVszDSBTD7NIoXOgRZic95_wfq6mM7b9ZS5Hv2q0ZkJHrhB2FOUeVY5iO2q-GX0h18Vas1uaAOCMf8EiJCgPVbecn426rICW0tCsJukQcgkkXwqmdYvPz8Tge9Xxx8uZT1iwM3OzDmIJdIz6jAXEIqtSVpDV9aQyfq1IuKDV)

## Initialization

For this example system, the `initialize()` method is overridden to ‘detect’ two doors.

```cpp
for (uint i = 0; i < numDoors; i++)
{
    FCM_PREPARE_MESSAGE(doorDetectedInd, Sensing, DoorDetectedInd);
    doorDetectedInd->doorId = i;
    FCM_SEND_MESSAGE(doorDetectedInd, i);
}
```

## Functions overview

The functions interface of the Sensor Handler is given in the table below for this test application, are stubbed and immediately send the expected reply.

<table>
  <tr>
   <td>Name
   </td>
   <td>Description
   </td>
   <td>Parameter
   </td>
   <td>Type
   </td>
  </tr>
  <tr>
   <td><code>enableLockSensor</code>
   </td>
   <td>Enable the door lock sensor.
   </td>
   <td><code>doorId</code>
   </td>
   <td><code>uint</code>
   </td>
  </tr>
  <tr>
   <td><code>enableDoorSensor</code>
   </td>
   <td>Enable the door sensor.
   </td>
   <td><code>doorId</code>
   </td>
   <td><code>uint</code>
   </td>
  </tr>
  <tr>
   <td><code>lock</code>
   </td>
   <td>Lock the door.
   </td>
   <td><code>doorId</code>
   </td>
   <td><code>uint</code>
   </td>
  </tr>
  <tr>
   <td><code>unlock</code>
   </td>
   <td>Unlock the door.
   </td>
   <td><code>doorId</code>
   </td>
   <td><code>uint</code>
   </td>
  </tr>
  <tr>
   <td rowspan="2" ><code>addTag</code>
   </td>
   <td rowspan="2" >Add a tag to the internal list.
   </td>
   <td><code>doorId</code>
   </td>
   <td><code>uint</code>
   </td>
  </tr>
  <tr>
   <td><code>tagId</code>
   </td>
   <td><code>uint</code>
   </td>
  </tr>
  <tr>
   <td rowspan="2" ><code>removeTag</code>
   </td>
   <td rowspan="2" >Remove the tag from the internal list
   </td>
   <td><code>doorId</code>
   </td>
   <td><code>uint</code>
   </td>
  </tr>
  <tr>
   <td><code>tagId</code>
   </td>
   <td><code>uint</code>
   </td>
  </tr>
</table>

In addition to the mentioned functions, there are two test functions specified which can mimic opening and closing a door.

```cpp
void sendDoorSensorInd(uint doorId, bool open);
void sendLockSensorInd(uint doorId, bool locked);
```

# Door Controller
_The Door Controller monitors and controls the lock and monitors the status of the door._

---

## Context

The context of the Door Controller is given in the figure below.

![](https://www.plantuml.com/plantuml/img/NL512i8m4Bpd5KjFUeW7Rq85GH4zzsX5GhijnNHNaWXMyUychQsjnypCpinkDjOfu-wr5lPQqKqPLKF6zOq9oIMkqGW6CwUer3YIl0J0aHoQGcMuPo-jdWXhM8ct4CEyTo9dM6iqe2n4IMCTrYbj1pWIWZX7i4YMpK5HFcXR9AKlveL33rW-V07VO3Rl4ovLqKvzdK_dgAE3RqLbJoVTCz2U__NCcRlK7OVCIJyORo7bAF571N_PkWHzwnRBKNX0folA2VtFnej5v-QlAJP8kV-W3m00)

## References

The handler references for the Door Controller are given in the following table.

<table>
  <tr>
   <td>Reference
   </td>
   <td>Type
   </td>
  </tr>
  <tr>
   <td><code>sensorHandler</code>
   </td>
   <td><code>std::shared_ptr&lt;SensorHandler></code>
   </td>
  </tr>
</table>

## Settings

The settings for the Door Controller are given in the following table.

<table>
  <tr>
   <td>Name
   </td>
   <td>Type
   </td>
   <td>Description
   </td>
  </tr>
  <tr>
   <td><code>openDoorTimeoutMs</code>
   </td>
   <td><code>long long</code>
   </td>
   <td>The time it is allowed to have the door open in milliseconds.
   </td>
  </tr>
</table>

## State variables

The state variables for the Door Controller are given in the following table.

<table>
  <tr>
   <td>Name
   </td>
   <td>Type
   </td>
   <td>Description
   </td>
  </tr>
  <tr>
   <td><code>openDoorTimerId</code>
   </td>
   <td><code>int</code>
   </td>
   <td>The timer to handle open door timeouts.
   </td>
  </tr>
  <tr>
   <td><code>doorId</code>
   </td>
   <td><code>uint</code>
   </td>
   <td>The identification number of the door.
   </td>
  </tr>
  <tr>
   <td><code>lockState</code>
   </td>
   <td><code>bool</code>
   </td>
   <td>Detected value of the lock sensor.
   </td>
  </tr>
  <tr>
   <td><code>doorState</code>
   </td>
   <td><code>bool</code>
   </td>
   <td>Detected value of the door sensor.
   </td>
  </tr>
</table>

## Behavior

When the Door Controller starts, it needs to wait for a door to be detected and assigned to it. This happens when the `Sensing:DoorDetectedInd` is received. The id of the door contained in the message is then stored in the `doorId` state variable.

However, although the door is detected, its door sensor is not enabled yet, i.e. the door is not released for operation. This can be done when the `Control:ReleaseDoorInd` is revived. Upon receiving this message, the Door Controller can first enable the door sensor by calling the `enableDoorSensor()` function of the Sensor Handler.

Consequently, the door sensor will respond with its current status via the `Sensing:DoorSensorInd`.

Only when the door is closed will the lock sensor be operational. Thus, in that case, the lock sensor can be triggered to (re)send its state by calling the `triggerLockSensor()` function of the Sensor Handler.

When the door is opened, a timer needs to be started to detect when the door is opened too long.

In order to lock or unlock the door, the `Control:SetLockInd` message is used. This command can only be handled when the door is closed. Otherwise, the `Control:Error message` is replied.

No explicit reply is required for the `Control:SetLockInd` message because the result of the operation is received via the `Sensing:LockSensorInd` message.

When a door is opened or closed, the Sensing:DoorSensorInd message is received which can be forwarded via the `Control:DoorStateChangedInd` message.

When the door is locked, tags can be added or removed from the door’s internal tag administration. Tags are stored at the door itself to allow a door to operate even if the network is down.

## States

The states for the Door Controller are given in the following table.

<table>
  <tr>
   <td>State
   </td>
   <td>Description
   </td>
  </tr>
  <tr>
   <td>Idle
   </td>
   <td>No door is detected yet and the <code>Sensing:DoorDetectedInd</code> is awaited.
   </td>
  </tr>
  <tr>
   <td>Standby
   </td>
   <td>Before the door can be used, it must be released for operation and its state must be retrieved.
   </td>
  </tr>
  <tr>
   <td>Await Door Sensor
   </td>
   <td>Waiting for the door sensor to supply its status.
   </td>
  </tr>
  <tr>
   <td>Locked
   </td>
   <td>The door is closed and locked.
   </td>
  </tr>
  <tr>
   <td>Unlocked
   </td>
   <td>The door is closed, but unlocked.
   </td>
  </tr>
  <tr>
   <td>Open
   </td>
   <td>The door is open.
   </td>
  </tr>
  <tr>
   <td>Await Lock Sensor
   </td>
   <td>Waiting for the lock sensor to supply its information.
   </td>
  </tr>
  <tr>
   <td>Locking
   </td>
   <td>The door is being locked.
   </td>
  </tr>
  <tr>
   <td>Unlocking
   </td>
   <td>The door is being unlocked.
   </td>
  </tr>
</table>

## Choice-points

The choice-points defined for the Door Controller are given in the following table.

<table>
  <tr>
   <td>Choice-point
   </td>
   <td>Evaluation
   </td>
  </tr>
  <tr>
   <td>Closed?
   </td>
   <td>Whether the door sensor detected that the door is closed, i.e. the value of <code>doorState</code>.
   </td>
  </tr>
  <tr>
   <td>Is locked?
   </td>
   <td>Whether the lock sensor detected that the door is locked, i.e. the value of <code>lockState</code>.
   </td>
  </tr>
</table>

## State diagram

The state diagram for the Door Controller is given in the figure below.

![](https://www.plantuml.com/plantuml/img/ZPJHIiCm58RlynIXby8Um5xCZOx1OAZOUI5E93Q76POc9SaSK_Rk9cdIrDAfDoF9-Sxv__ziRAODKUPGS_JEA62e6tF257IbM6EO50ZfFHCDKQJ6SwNa4NyXZ9TIc99z0hv6PqiOOW1NicumqJXRIAbmOGabEGULsOw0h2Y7S2mD4VJj56wFOY_aKVZs-P4mWzsGhIX1QAcoGArbjGVQjV3-zQu14Ov-W6FRxjvGzpWsb8dTZwdk7XwA-rUcMs4_QAMtGVWcIqZ5fGv0uO-sY9wlNl1aCcrJ8_Vfho4vpfqFgvIxg0imK1cWAq4HYeIZusRokD7y0JWG3QxBqv5mTBAIu_xuDhB74sBvuQfo_0IwZrZ6RTOMRYL2Gpn8TWjAeWcAeXraUpeygAMQJynZsMbw-P_FuybQC1cE-oh1MxR8LcnO3V9WtD9uKlpB_RYv5XYmwv6fqSYSqWtP5RNraRxBMdw0VHqu2X76WoPo6d-zet5RuwxwZv1zT6JLhhmaZ8_luxA3LFzby33QHSjjkVDnHZCGrFvtVGC0)

## State transition table

The state transition table for the Door Controller is given in the following table.

<table>
  <tr>
   <td>State
   </td>
   <td>Interface
   </td>
   <td>Message
   </td>
   <td>Next state
   </td>
   <td>Actions
   </td>
  </tr>
  <tr>
   <td>Idle
   </td>
   <td><code>Sensing</code>
   </td>
   <td><code>DoorDetectedInd</code>
   </td>
   <td>Standby
   </td>
   <td>
<ul>

<li>Set <code>doorId</code>.

<li>Send <code>Control:DoorDetectedInd</code>.
</li>
</ul>
   </td>
  </tr>
  <tr>
   <td>Standby
   </td>
   <td><code>Control</code>
   </td>
   <td><code>ReleaseDoorInd</code>
   </td>
   <td>Await Door Sensor
   </td>
   <td>
<ul>

<li>Call <code>sensorHandler:enableDoorSensorInd()</code>.
</li>
</ul>
   </td>
  </tr>
  <tr>
   <td>Await Door Sensor
   </td>
   <td><code>Sensing</code>
   </td>
   <td><code>DoorSensorInd</code>
   </td>
   <td>Closed?
   </td>
   <td>
<ul>

<li>Set <code>doorState</code>.

<li>Call <code>sendDoorStateChangedInd()</code>.
</li>
</ul>
   </td>
  </tr>
  <tr>
   <td rowspan="2" >Closed?
   </td>
   <td rowspan="2" ><code>Logical</code>
   </td>
   <td><code>Yes</code>
   </td>
   <td>Await Lock Sensor
   </td>
   <td>
<ul>

<li>Call <code>sensorHandler:enableLockSensor()</code>.
</li>
</ul>
   </td>
  </tr>
  <tr>
   <td><code>No</code>
   </td>
   <td>Open
   </td>
   <td>
<ul>

<li>Start <code>openDoorTimer</code>.
</li>
</ul>
   </td>
  </tr>
  <tr>
   <td>Await Lock Sensor
   </td>
   <td><code>Sensing</code>
   </td>
   <td><code>LockSensorInd</code>
   </td>
   <td>Is Locked?
   </td>
   <td>
<ul>

<li>Set <code>lockSensor</code>.

<li>Call <code>sendDoorLockChangedInd()</code>.
</li>
</ul>
   </td>
  </tr>
  <tr>
   <td rowspan="2" >Is Locked
   </td>
   <td rowspan="2" ><code>Logical</code>
   </td>
   <td><code>Yes</code>
   </td>
   <td>Locked
   </td>
   <td>
<ul>

<li>-
</li>
</ul>
   </td>
  </tr>
  <tr>
   <td><code>No</code>
   </td>
   <td>Unlocked
   </td>
   <td>
<ul>

<li>-
</li>
</ul>
   </td>
  </tr>
  <tr>
   <td rowspan="3" >Open
   </td>
   <td><code>Sensing</code>
   </td>
   <td><code>DoorSensorInd</code>
   </td>
   <td>Unlocked
   </td>
   <td>
<ul>

<li>Set <code>doorState</code>.

<li>Call <code>sendDoorStateChangedInd()</code>.

<li>Cancel <code>openDoorTimer</code>.
</li>
</ul>
   </td>
  </tr>
  <tr>
   <td><code>Control</code>
   </td>
   <td><code>SetLockInd</code>
   </td>
   <td>Open
   </td>
   <td>
<ul>

<li>Send <code>Control:ErrorInd</code>.
</li>
</ul>
   </td>
  </tr>
  <tr>
   <td><code>Timer</code>
   </td>
   <td><code>Timeout</code>
   </td>
   <td>Open
   </td>
   <td>
<ul>

<li>Send <code>Control:AlarmInd</code>.
</li>
</ul>
   </td>
  </tr>
  <tr>
   <td rowspan="3" >Unlocked
   </td>
   <td rowspan="2" ><code>Sensing</code>
   </td>
   <td><code>LockSensorInd</code>
   </td>
   <td>Locked
   </td>
   <td>
<ul>

<li>Call <code>sendDoorLockChangedInd()</code>.
</li>
</ul>
   </td>
  </tr>
  <tr>
   <td><code>DoorSensorInd</code>
   </td>
   <td>Open
   </td>
   <td>
<ul>

<li>Call <code>sendDoorStateChangedInd()</code>.

<li>Start <code>openDoorTimer</code>.
</li>
</ul>
   </td>
  </tr>
  <tr>
   <td><code>Control</code>
   </td>
   <td><code>SetLockInd</code>
   </td>
   <td>Locking
   </td>
   <td>
<ul>

<li>Call <code>sensorHandler:lock()</code>.
</li>
</ul>
   </td>
  </tr>
  <tr>
   <td rowspan="2" >Locking
   </td>
   <td rowspan="2" ><code>Sensing</code>
   </td>
   <td><code>LockSensorInd</code>
   </td>
   <td>Locked
   </td>
   <td>
<ul>

<li>Call <code>sendDoorLockChangedInd()</code>.
</li>
</ul>
   </td>
  </tr>
  <tr>
   <td><code>LockFailInd</code>
   </td>
   <td>Unlocked
   </td>
   <td>
<ul>

<li>Send <code>Control:ErrorInd</code>.
</li>
</ul>
   </td>
  </tr>
  <tr>
   <td rowspan="4" >Locked
   </td>
   <td rowspan="3" ><code>Control</code>
   </td>
   <td><code>SetLockInd</code>
   </td>
   <td>Unlocking
   </td>
   <td>
<ul>

<li>Call <code>sensorHandler:unlock()</code>.
</li>
</ul>
   </td>
  </tr>
  <tr>
   <td><code>AddTagInd</code>
   </td>
   <td>Locked
   </td>
   <td>
<ul>

<li>Call <code>sensorHandler:addTag()</code>.
</li>
</ul>
   </td>
  </tr>
  <tr>
   <td><code>RemoveTagInd</code>
   </td>
   <td>Locked
   </td>
   <td>
<ul>

<li>Call <code>sensorHandler:removeTag()</code>.
</li>
</ul>
   </td>
  </tr>
  <tr>
   <td><code>Sensing</code>
   </td>
   <td><code>LockSensorInd</code>
   </td>
   <td>Unlocked
   </td>
   <td>
<ul>

<li>Call <code>sendDoorLockChangedInd()</code>.
</li>
</ul>
   </td>
  </tr>
  <tr>
   <td rowspan="2" >Unlocking
   </td>
   <td rowspan="2" ><code>Sensing</code>
   </td>
   <td><code>LockSensorInd</code>
   </td>
   <td>Unlocked
   </td>
   <td>
<ul>

<li>Call <code>sendDoorLockChangedInd()</code>.
</li>
</ul>
   </td>
  </tr>
  <tr>
   <td><code>UnlockFailInd</code>
   </td>
   <td>Locked
   </td>
   <td>
<ul>

<li>Send <code>Control:ErrorInd</code>.
</li>
</ul>
   </td>
  </tr>
</table>

## Local functions

The local functions that are used in the transition code are listed in the following table.

<table>
  <tr>
   <td>Function
   </td>
   <td>Description
   </td>
   <td>Parameter
   </td>
   <td>Type
   </td>
  </tr>
  <tr>
   <td><code>sendDoorLockChangedInd()</code>
   </td>
   <td>The door lock changed and  the <code>Sensing:DoorLockChangedInd</code> message will be sent.
   </td>
   <td><code>lock</code>
   </td>
   <td><code>bool</code>
   </td>
  </tr>
  <tr>
   <td><code>sendDoorStateChangedInd()</code>
   </td>
   <td>The door lock changed and  the <code>Sensing:DoorStateChangedInd</code> message will be sent.
   </td>
   <td><code>open</code>
   </td>
   <td><code>bool</code>
   </td>
  </tr>
</table>

# Administrator
_The Administrator is responsible for initializing the database, supplying system settings and storing events in the database to maintain the system history._

---

## Context

The context of the Administrator is given in the figure below.

![](https://www.plantuml.com/plantuml/img/LP2x3i8m34LtVqMK2OPy00DI4GY9cRKICgsB8X879UvG4FzE-g2KBRe-zyHoaGIZjDv1kbj-O4Ilgk0VWOdbB9qZ5QaIv9kZ1V82fKui51kiw1WoQf-ajce3Ru2vdqqiCJX7KM5I-jmb8L_oVexr0iRQMxP98aeO-TqoqG0SQkgTZRqDy_tmRFFO1YxvW89NJ9J9rNhKNMppC-a-7klVV3Ja0YnMDNCNPedvssx09usPbF2_l_dz150Gr_d67m00)

## References

The handler references for the Administrator are given in the following table.

<table>
  <tr>
   <td>Reference
   </td>
   <td>Type
   </td>
  </tr>
  <tr>
   <td><code>configurationDatabase</code>
   </td>
   <td><code>std::shared_ptr&lt;ConfigurationDatabase></code>
   </td>
  </tr>
</table>

## Settings

The Administrator has no settings.

## State variables

The state variables for the Administrator are given in the following table.

<table>
  <tr>
   <td>Name
   </td>
   <td>Type
   </td>
   <td>Description
   </td>
  </tr>
  <tr>
   <td><code>pendingEvents</code>
   </td>
   <td><code>std:list&lt;string></code>
   </td>
   <td>List of events that still need to be stored.
   </td>
  </tr>
</table>


## Behavior

When the Administrator initializes, it needs to also initialize the Configuration Database by calling its `initDatabase()` function. When the database is initialized, the `Config:InitializedInd` message is received.

When the Configuration Database is initialized, the Administrator can receive the `Admin:GetBackendUrlReq` which is a request to retrieve the backend URL. As a result it calls the `getBackendUrl()` of the Configuration Database. When the database extracted the backend URL, the Administrator received the `Config:BackendUrlInd` message. This is forwarded by sending the `Admin:GetBackendUrlRsp` message.

The Administrator converts the messages on the Admin interface to a proper event description and adds this to the database by calling the `storeEvent()` function of the Configuration Database. When the database has properly stored the event, the `Config:eventStoredInd` is received. Only one event can be stored each time, so storing any intermediate events is postponed.

## Initialization

As stated, when the Administrator initializes, it needs to also initialize the Configuration Database. Therefore, the default `initialize()` method of the Administrator must be overridden and the first step is to call the base class `initialize()` method.

```cpp
FcmFunctionalComponent::initialize();
```

To initialize the database its `initDatabase()` function is called.

```cpp
configurationDatabase->initDatabase();
```

As stated, when the database is initialized, the `Config:InitializedInd` message is received.

## States

The states for the Administrator are given in the following table.

<table>
  <tr>
   <td>State
   </td>
   <td>Description
   </td>
  </tr>
  <tr>
   <td>Idle
   </td>
   <td>
   </td>
  </tr>
  <tr>
   <td>Standby
   </td>
   <td>The system is initializing and the Administrator awaits for the request to retrieve settings.
   </td>
  </tr>
  <tr>
   <td>Retrieving
   </td>
   <td>Waiting to receive the settings from the database.
   </td>
  </tr>
  <tr>
   <td>Ready
   </td>
   <td>Ready to handle events.
   </td>
  </tr>
  <tr>
   <td>Storing
   </td>
   <td>Busy storing an event in the database.
   </td>
  </tr>
</table>

## Choice-points

The choice-points defined for the Administrator are given in the following table.

<table>
  <tr>
   <td>Choice-point
   </td>
   <td>Evaluation
   </td>
  </tr>
  <tr>
   <td>Pending events?
   </td>
   <td>Whether there are pending events, i.e. whether <code>pendingEvents</code> contains elements.
   </td>
  </tr>
</table>

## State diagram

The state diagram for the Administrator is given in the figure below.

![](https://www.plantuml.com/plantuml/img/hPBFJiCm3CRlVWfhHwG-03l0nlYZIGXDgpWWXb1eJ1UjTKfYXWRYtKdJh1qQHovHxEzd-tEKYHVbvBskO6qq8TMDx52JBvnfn5W6y1l3ZNAgngbpzWE_0F7QikJca_0KlWCXIWWBMpUeF8wckZPil3Wbreq2du2vhYXTSr6iNtOfMf8uGrl3PPzGUjUZrhLA2cUBvmMn3fchBR7uE35bLjpbpaS0ZoTFc9rrCw4zsoYDnJ7EBB-QSZnd8qPLOHCzPmsm1x803wu27tSQtv1Sg68JfjsxQabl00TGLnEC3-q7E7RlrEWZxjJtlRJMvUrwixNYCdfPyI3Tsc8pAAtBhZpxtrP7Jzll4UCMJLL7v6yd3-J_HlRFSsSX_9j9qCF7-m40)

## State transition table

The state transition table for the Administrator is given in the following table.

<table>
  <tr>
   <td>State
   </td>
   <td>Interface
   </td>
   <td>Message
   </td>
   <td>Next state
   </td>
   <td>Actions
   </td>
  </tr>
  <tr>
   <td>Idle
   </td>
   <td><code>Config</code>
   </td>
   <td><code>InitializedInd</code>
   </td>
   <td>Standby
   </td>
   <td>
<ul>

<li>-
</li>
</ul>
   </td>
  </tr>
  <tr>
   <td>Standby
   </td>
   <td><code>Admin</code>
   </td>
   <td><code>BackendUrlReq</code>
   </td>
   <td>Retrieving
   </td>
   <td>
<ul>

<li>Call <code>configDatabase:getBackendUrl()</code>.
</li>
</ul>
   </td>
  </tr>
  <tr>
   <td>Retrieving
   </td>
   <td><code>Config</code>
   </td>
   <td><code>BackendUrlInd</code>
   </td>
   <td>Ready
   </td>
   <td>
<ul>

<li>Send <code>Admin:BackendUrlRsp</code>.
</li>
</ul>
   </td>
  </tr>
  <tr>
   <td rowspan="2" >Ready
   </td>
   <td rowspan="2" ><code>Admin</code>
   </td>
   <td><code>DoorStateChangedInd</code>
   </td>
   <td>Storing
   </td>
   <td>
<ul>

<li>Create the event string.

<li>Call <code>configDatabase:storeEvent()</code>.
</li>
</ul>
   </td>
  </tr>
  <tr>
   <td><code>DoorLockChangedInd</code>
   </td>
   <td>Storing
   </td>
   <td>
<ul>

<li>Create the event string.

<li>Call <code>configDatabase:storeEvent()</code>.
</li>
</ul>
   </td>
  </tr>
  <tr>
   <td rowspan="3" >Storing
   </td>
   <td rowspan="2" ><code>Admin</code>
   </td>
   <td><code>DoorStateChangedInd</code>
   </td>
   <td>Storing
   </td>
   <td>
<ul>

<li>Create the event string.

<li>Add string to <code>pendingEvents</code>.
</li>
</ul>
   </td>
  </tr>
  <tr>
   <td><code>DoorLockChangedInd</code>
   </td>
   <td>Storing
   </td>
   <td>
<ul>

<li>Create the event string.

<li>Add string to <code>pendingEvents</code>.
</li>
</ul>
   </td>
  </tr>
  <tr>
   <td><code>Config</code>
   </td>
   <td><code>EventStoredInd</code>
   </td>
   <td>Pending Events?
   </td>
   <td>
<ul>

<li>-
</li>
</ul>
   </td>
  </tr>
  <tr>
   <td rowspan="2" >Pending Events?
   </td>
   <td rowspan="2" ><code>Logical</code>
   </td>
   <td><code>Yes</code>
   </td>
   <td>Storing
   </td>
   <td>
<ul>

<li>Pop the next event string.

<li>Call <code>configDatabase:storeEvent()</code>.
</li>
</ul>
   </td>
  </tr>
  <tr>
   <td><code>No</code>
   </td>
   <td>Ready
   </td>
   <td>
<ul>

<li>-
</li>
</ul>
   </td>
  </tr>
</table>

# System Controller
_The System Controller is responsible for the overall system control. It manages the doors and forwards the commands to the backend. It also forwards the state changes of the doors to the backend._

---

## Context

The context of the System Controller is given in the figure below.

![](https://www.plantuml.com/plantuml/img/PLAnJaCn3Dpp5TQRO7WTs2e1AhH2wjoH8XHUN1GrSQeaI1J4l-EuRLwUkYM-yvtFoI9b7VENTohjBHrqr1w6u0-1aF8c7nr2n25h-dJOK7uLm9eonfqUy2KmrVuWFC1S_IbL-rc9SWpEOGITeDiSKqQ_fMKjTmrP6s_9fXnr3YV-KrlfbA9W43xqi4SorLsOpwVYbcgPwJUt9OhNPDAxtGblURvt1HJ32o9Ut5JJmjqtn-IS8YC3ZofoVNth2ZucCE4y-8eFqvZ2gyle-qPoX8f-BofbZLT1fQlckSRlPxF6HDwXXkyV9z1qronysOLgfnohQi5E_4l-0G00)

## References

The handler references for the System Controller are given in the following table.

<table>
  <tr>
   <td>Reference
   </td>
   <td>Type
   </td>
   <td>Description
   </td>
  </tr>
  <tr>
   <td><code>backendInterface</code>
   </td>
   <td><code>BackendInterface</code>
   </td>
   <td>Backend Interface handler.
   </td>
  </tr>
</table>

## Settings

The settings for the System Controller are given in the following table.

<table>
  <tr>
   <td>Name
   </td>
   <td>Type
   </td>
   <td>Description
   </td>
  </tr>
  <tr>
   <td><code>numDoors</code>
   </td>
   <td><code>uint</code>
   </td>
   <td>Number of doors to be detected.
   </td>
  </tr>
</table>

## State variables

The state variables for the System Controller are given in the following table.

<table>
  <tr>
   <td>Name
   </td>
   <td>Type
   </td>
   <td>Description
   </td>
  </tr>
  <tr>
   <td><code>detectedDoors</code>
   </td>
   <td><code>std:vector&lt;uint></code>
   </td>
   <td>The detected doors that can be controlled.
   </td>
  </tr>
  <tr>
   <td><code>lastDoorIndex</code>
   </td>
   <td><code>int</code>
   </td>
   <td>The index of the last door for which a command was received.
   </td>
  </tr>
  <tr>
   <td><code>lastDoorId</code>
   </td>
   <td><code>uint</code>
   </td>
   <td>The id of the last door for which a command was received.
   </td>
  </tr>
</table>

## Behavior

When the System Controller starts, it first needs to wait for all the doors to be discovered. The number of doors is supplied as a setting.

The detection of a door is received via the `Control:DoorDetectedInd` message.

After all doors are detected, the system is ready to connect to the backend via the Backend Interface. However, in order to do that, it requires the URL of the backend. This can be retrieved via the `Admin:GetBackendUrlReq` message. When the expected `Admin:GetBackendUrlRsp` response is received, the `Backend Interface` can be instructed to connect by calling its `connect()` function.

When the backend is connected, the `Commands:ConnectedInd` is received. With the connection established, the doors can be released for operation. This is done by sending a `Control:ReleaseDoorInd` message to each instance of the Control interface.

After this is done, the system is ready to receive commands from the backend via the `Commands` interface:

* `LockDoorInd` \
  Lock the specified door.
* `UnlockDoorInd` \
  Unlock the specified door.
* `AddTagInd` \
  Add the specified tag to the database. No response is required.
* `RemoveTagInd` \
  Remove the specified tag from the database. No response is required.

When the state of a door changes, the `Control:DoorStateChangedInd` is received. Likewise, when the door is locked or unlocked, the `Control:DoorLockChangedInd` is received. These are forwarded to the Backend Interface by calling its `doorStateChanged()` and `doorLockStateChanged()` functions respectively.

Any state change needs to be supplied to the database as well to keep the history. This is done by sending the `Admin:DoorStateChangedInd` and `Admin:DoorLockChangedInd` respectively.

When an alarm or error occurs with one of the doors, the `Control:ErrorInd` or `Control:AlarmInd` messages are received respectively. These are forwarded to the backend by calling the `error()` and `alarm()` functions.

## States

The states for the System Controller are given in the following table.

<table>
  <tr>
   <td>State
   </td>
   <td>Description
   </td>
  </tr>
  <tr>
   <td>Awaiting Doors
   </td>
   <td>Waiting for all doors to be detected.
   </td>
  </tr>
  <tr>
   <td>Initializing
   </td>
   <td>Waiting to receive the initialization settings.
   </td>
  </tr>
  <tr>
   <td>Ready
   </td>
   <td>Ready to control doors.
   </td>
  </tr>
  <tr>
   <td>Connecting
   </td>
   <td>Connecting to the backend.
   </td>
  </tr>
</table>


## Choice-points

The choice-points defined for the System Controller are given in the following table.

<table>
  <tr>
   <td>Choice-point
   </td>
   <td>Evaluation
   </td>
  </tr>
  <tr>
   <td>All Doors Detected?
   </td>
   <td>Whether all doors are detected, i.e. check if the size of <code>detectedDoors</code> is equal to the <code>numDoors</code> setting.
   </td>
  </tr>
  <tr>
   <td>Door found?
   </td>
   <td>Whether the door for which the backend issued an action is found.
   </td>
  </tr>
</table>

## State diagram

The state diagram for the System Controller is given in the figure below.

![](https://www.plantuml.com/plantuml/img/hLFDJW8n4BxtAHgE9Zo0Ur1M44DY304v636csKwWePrYMoHWU7UdfRYxkaTlkz_FVFEpE_11kB0pcgsL10vc6mvSWg-SsWPbaJ6_KRWLJXXUEcVt_8jnFhOOvke8_9gTI15405vPi-N2yzxyu0COFYIDirg3wv4dYygzK47XQcIjyqbzGPQOi5uMJf1GeTMHg0nHGOGgrC0CX3pavwcp5NWVoOjy-bvgdOfE7NZ0SCxJEaSjCUEtlTeIcR7TeKpY-BR4z4uYzdhrnllzc_OKZBM78huZkhZieuZm209D0dA2ah4ETGnfRe3iB-0xbR-w8UMJfPe_kqgrqgPI3yO8bBx8VEw0jRAYeU4lU2cDmk81mfseDe1ouVGCFiXsBjiEg8USnvqErm9NAMQ9JVBHLfikxfw-CTT2IYsSIMtMSQr3DSOgfNmMgspFs0oC_OG_S6mWrcYZ2zGrdavJvr1k_PNL5sa86ek8HsYeEu_mtzsUs82kG__oDm00)

## State transition table

The state transition table for the System Controller is given in the following table.

<table>
  <tr>
   <td>State
   </td>
   <td>Interface
   </td>
   <td>Message
   </td>
   <td>Next state
   </td>
   <td>Actions
   </td>
  </tr>
  <tr>
   <td>Awaiting Doors
   </td>
   <td><code>Control</code>
   </td>
   <td><code>DoorDetectedInd</code>
   </td>
   <td>All Doors Detected?
   </td>
   <td>
<ul>

<li>Add detected door to <code>detectedDoors</code>.
</li>
</ul>
   </td>
  </tr>
  <tr>
   <td rowspan="2" >All Doors Detected?
   </td>
   <td rowspan="2" ><code>Logical</code>
   </td>
   <td><code>Yes</code>
   </td>
   <td>Initializing
   </td>
   <td>
<ul>

<li>Send <code>Admin:BackendUrlReq.</code>
</li>
</ul>
   </td>
  </tr>
  <tr>
   <td><code>No</code>
   </td>
   <td>Awaiting Doors
   </td>
   <td>
<ul>

<li>-
</li>
</ul>
   </td>
  </tr>
  <tr>
   <td>Initializing
   </td>
   <td><code>Admin</code>
   </td>
   <td><code>BackendUrlRsp</code>
   </td>
   <td>Connecting
   </td>
   <td>
<ul>

<li>Call <code>backendInterface:connect()</code>.
</li>
</ul>
   </td>
  </tr>
  <tr>
   <td>Connecting
   </td>
   <td><code>Commands</code>
   </td>
   <td><code>ConnectedInd</code>
   </td>
   <td>Ready
   </td>
   <td>
<ul>

<li>Send <code>Control:ReleaseDoorInd</code> to each instance.
</li>
</ul>
   </td>
  </tr>
  <tr>
   <td rowspan="8" >Ready
   </td>
   <td rowspan="4" ><code>Commands</code>
   </td>
   <td><code>LockDoorInd</code>
   </td>
   <td>Door Found?
   </td>
   <td>
<ul>

<li>Set <code>lastDoorId</code>.

<li>Set `lastDoorIndex`to result from `findDoorIndex()`.
</ul>
   </td>
  </tr>
  <tr>
   <td><code>UnlockDoorInd</code>
   </td>
   <td>Door Found?
   </td>
   <td>
<ul>

<li>Set <code>lastDoorId</code>.

<li>Set `lastDoorIndex`to result from `findDoorIndex()`.
</ul>
   </td>
  </tr>
  <tr>
   <td><code>AddTagInd</code>
   </td>
   <td>Door Found?
   </td>
   <td>
<ul>

<li>Set <code>lastDoorId</code>.

<li>Set `lastDoorIndex`to result from `findDoorIndex()`.
</ul>
   </td>
  </tr>
  <tr>
   <td><code>RemoveTagInd</code>
   </td>
   <td>Door Found?
   </td>
   <td>
<ul>

<li>Set <code>lastDoorId</code>.

<li>Set `lastDoorIndex`to result from `findDoorIndex()`.
</ul>
   </td>
  </tr>
  <tr>
   <td rowspan="4" ><code>Control</code>
   </td>
   <td><code>DoorStateChangedInd</code>
   </td>
   <td>Ready
   </td>
   <td>
<ul>

<li>Send <code>Admin:DoorStateChangedInd</code>.

<li>Call <code>backendInterface:doorStateChanged()</code>.
</li>
</ul>
   </td>
  </tr>
  <tr>
   <td><code>DoorLockChangedInd</code>
   </td>
   <td>Ready
   </td>
   <td>
<ul>

<li>Send <code>Admin:DoorLockChangedInd</code>.

<li>Call <code>backendInterface:doorLockChanged()</code>.
</li>
</ul>
   </td>
  </tr>
  <tr>
   <td><code>ErrorInd</code>
   </td>
   <td>Ready
   </td>
   <td>
<ul>

<li>Call <code>backendInterface:error()</code>.
</li>
</ul>
   </td>
  </tr>
  <tr>
   <td><code>AlarmInd</code>
   </td>
   <td>Ready
   </td>
   <td>
<ul>

<li>Call <code>backendInterface:alarm()</code>.
</li>
</ul>
   </td>
  </tr>
  <tr>
   <td rowspan="2" >Door Found?
   </td>
   <td rowspan="2" ><code>Logical</code>
   </td>
   <td><code>Yes</code>
   </td>
   <td>Processing
   </td>
   <td>
<ul>

<li>Call <code>resendLastReceivedMessage()</code>.
</li>
</ul>
   </td>
  </tr>
  <tr>
   <td><code>No</code>
   </td>
   <td>Processing
   </td>
   <td>
<ul>

<li>-
</li>
</ul>
   </td>
  </tr>
  <tr>
   <td rowspan="4" >Processing
   </td>
   <td rowspan="4" ><code>Commands</code>
   </td>
   <td><code>LockDoorInd</code>
   </td>
   <td>Ready
   </td>
   <td>
<ul>

<li>Send <code>Control:SetLockInd</code> to proper instance.
</li>
</ul>
   </td>
  </tr>
  <tr>
   <td><code>UnlockDoorInd</code>
   </td>
   <td>Ready
   </td>
   <td>
<ul>

<li>Send <code>Control:SetLockInd</code> to proper instance.
</li>
</ul>
   </td>
  </tr>
  <tr>
   <td><code>AddTagInd</code>
   </td>
   <td>Ready
   </td>
   <td>
<ul>

<li>Send <code>Control:AddTagInd</code> to proper instance.
</li>
</ul>
   </td>
  </tr>
  <tr>
   <td><code>RemoveTagInd</code>
   </td>
   <td>Ready
   </td>
   <td>
<ul>

<li>Send <code>Control:RemoveTagInd</code> to proper instance.
</li>
</ul>
   </td>
  </tr>
</table>

## Find index of door

To find the index of a door with the specified id, the `findDoorIndex()` can  be called which returns -1 if the door was not found.

```cpp
int findDoorIndex(uint doorId);
```

# Device initialization
_When all required interfaces and components are defined, the device can be implemented as a subclass of the `FcmDevice` class._

---

## Class definition

For the Doors Controlling System a `DoorsControllerSystem` subclass of `FcmDevice` is defined which must override the virtual `initialize()` method from the base class. For the constructor it can be decided to add the number of doors as a parameter and set the timestamp as a constant.

```cpp
const uint TIMESTEP_MS = 100;
DoorsControllingSystem(uint numDoors) : FcmDevice(TIMESTEP_MS), numDoors(numDoors) {}
```

## Overview

As stated, the `initialize()` method needs to be overridden. Typically, in this method the following steps are implemented:

* Define the settings
* Create the components
* Set the references to handlers in the relevant functional components
* Connect the interfaces of the handlers
* Connect the functional components
* Initialize the created components

These steps are described in the following sections.

## Define settings

For the Doors Controlling System, the settings are the number of doors and the maximum time a door is allowed to be opened. These settings can be combined for convenience in one variable which can then be passed to the relevant components.

```cpp
std::map<std::string, std::any> settings;
settings["numDoors"] = numDoors;
settings["openDoorTimeoutMs"] = 60000; // 60 seconds
```

## Create components

With the settings defined, the components can be created by calling the `createComponents()` method which will also store the created component internally for iteration.

It is good practice to group to separate the creation of the asynchronous interface handlers from the functional components. As such, let’s first start with the creation of the handlers.

```cpp
// Create asynchronous interface handlers
auto backendInterface = createComponent<BackendInterface>("Backend Interface");
auto sensorHandler = createComponent<SensorHandler>("Sensor Handler");
auto configurationDatabase = createComponent<ConfigurationDatabase>("Configuration Database");
```

Then the functional components are created, starting with the Administrator and System Controller which needs the settings.

```cpp
// Create functional components
auto administrator = createComponent<Administrator>("Administrator");
auto systemController = createComponent<SystemController>("System Controller", settings);
```

A number of Door Controllers need to be created which all need the settings. The created Door Controllers will be stored in a vector in order to make it easier to iterate through them when setting the reference to the Sensor Handler and connecting the Sensor Handler to each Door Controller as described further on.

```cpp
std::vector<std::shared_ptr<DoorController>> doorControllers;
for (int i = 0; i < std::any_cast<int>(settings["numDoors"]); i++)
{
    auto doorController = createComponent<DoorController>("Door Controller", settings);
    doorControllers.push_back(doorController);
}
```

## Set references to handlers

The System Controller, Administrator and Door Controllers all have references to a handler as shown in the following figure.

![](https://www.plantuml.com/plantuml/img/PP51QWCn34NtEeMO0sJHNQ65j0cbMMSx6sMi11EF56m5cfRUlRPdS2PqPxwVxEVlTJAATXq3fBEN2qKQST3nei9YUxi5niY3aPm2Bv0VGDo9SJpIm1-QKV_D-8hFy0lGvlD9Ob53u8YKiDlVal7OowR5tG8cDthnoIAPJlpRCka0H1rZOaaQFqbSExOclSnPDt476iuihbbMz7qAUsdnJ6VJepzLPbENrtofL-bbIqO7IXc4rWG-VUKASWTtUwUpz5QBo_A9cNkKVbcjAb_A-gTPDk-zbJQhMOaV6W9OvxdySty0)

```cpp
// Set references to handlers.
systemController->setBackendInterface(backendInterface);
administrator->setConfigurationDatabase(configurationDatabase);
for (const auto& doorController : doorControllers)
{
    doorController->setSensorHandler(sensorHandler);
}
```

## Connect the interfaces of the handlers

Handlers can only transmit messages on their interfaces to a connected functional component. This is indicated by an arrow head at the functional component as indicated for the interfaces for the Doors Controlling System in the following figure.

![](https://www.plantuml.com/plantuml/img/PP8nJyCm48Lt_mhBKncoi24LL6Y5OCv84BecbyfgVAviLsf1_7VETkGwOelV-yxdUvUD3-32sKp27pMTm86HlJKdIqYX3TS9fSC-01qch90V8UKx1NGZzFXg6TNVA1_bW_WLejJpJHISdIPq4hnKxTK7D1rjYwmg60QZIVlW8DZCFzUA4eBiWD8ZUUlUW8PoRL8wcZMLkJtqHwIXl3AXBrdigCWppIyTzI4ns_HvvgRQKaSx2B07pw1OtSLi3BVnNtgSuNnMsOoLDokUkAm4AEyld1n7nsmSGrE1stpy-5JHluKos3cBdOqZrianbznrKrqMrML2pSBczVmBXebghBI_CcFpL2qnMYccL37FAfPxMzUMs70Z_hd-0000)

To be able to connect an interface to a remote receiver, the `FCM_CONNECT_INTERFACE`. This can be done for the Backend Interface and Configuration Database.

```cpp
FCM_CONNECT_INTERFACE(Commands, systemController, backendInterface);
FCM_CONNECT_INTERFACE(Config, configurationDatabase, administrator);
```

The Sensor Handler has a multiplicated “Sensing” interface to an instance of the Door Controller. As such the connection is performed a number of times.

```cpp
for (const auto& doorController : doorControllers)
{
    FCM_CONNECT_INTERFACE(Sensing, sensorHandler, doorController);
}
```

## Connect the functional components

For the other interfaces as shown in the figure below, the interface has functional components on both ends and are therefore bidirectional.

![](https://www.plantuml.com/plantuml/img/LP0z2y8m48Rt-nL79nswk3a85KLmTbIHq9uIJ2ubES4F_E-cjQPn2tTFte-hWYWlDsiWN3MtoYkBjREjOsBPoSCGUgf5ySLGXhm0SSj2_gngshY8wYVX0kVm1aZ_enABTyQGHnMms3s2a3tmAesB35QDrQo3U2Nkoo_pIG4mcNwXapwF-pXF2N5sZz5YjaWEtZzsyDmVYsu_kZPkC5l7nt-qdai5oZAJ75UTVjchTDLJlFA_3kH2gGH0HTp4uty0)

To connect both sides of an interface between two functional components, the convenience method `connectInterface()` of the Device can be called.

```cpp
FCM_CONNECT_INTERFACE(Admin, administrator, systemController);
for (const auto& doorController : doorControllers)
{
    FCM_CONNECT_INTERFACE(Control, doorController, systemController);
}
```

## Initialization the created components

As the final step, the created components must  be initialized. This is done by calling the `initializeCreatedComponents()` method.

```cpp
initializeComponents();
```

This method iterates through the Device’s `components` attribute and calls the `intiatialize()` method of each component.

By default, this method organizes the component to be ready to start. When specific initialization is required for a component, this must be explicitly programmed.

In the Doors Controlling System, this is only required for the Administrator.


# Main application
_The derived <code>DoorsControllingSystem</code> discussed in the previous chapter can now be used in the implementation of the main application._

---

## Creating the device

The first step is to create the device. In our case, this operation has one parameter being the number of doors which is stored in a constant.

```cpp
const uint NUM_DOORS = 2;
// ...
DoorsControllingSystem doorsControllingSystem{NUM_DOORS};
```

## Initialization

The initialization described in the previous chapter can now be called.

```cpp
doorsControllingSystem.initialize();
```

## Running

When the device is created and initialized it can be run from which the application will not return unless it is halted in some way.

```cpp
doorsControllingSystem.run();
return 0;
```