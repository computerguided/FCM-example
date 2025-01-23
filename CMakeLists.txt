cmake_minimum_required(VERSION 3.10)
project(DoorsControllingSystem)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-Wall -g -fno-rtti)
include_directories(inc sub/fcm/inc)

set(SOURCES
    main.cpp
    src/DoorsControllingSystem.cpp
    src/Administrator.cpp
    src/BackendInterface.cpp
    src/ConfigurationDatabase.cpp
    src/DoorController.cpp
    src/SensorHandler.cpp
    src/SystemController.cpp
    sub/fcm/src/FcmAsyncInterfaceHandler.cpp
    sub/fcm/src/FcmBaseComponent.cpp
    sub/fcm/src/FcmDevice.cpp
    sub/fcm/src/FcmFunctionalComponent.cpp
    sub/fcm/src/FcmMessageQueue.cpp
    sub/fcm/src/FcmTimerHandler.cpp
    sub/fcm/src/FcmWorkerHandler.cpp
)

add_executable(DoorsControllingSystem ${SOURCES})
