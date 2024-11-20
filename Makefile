# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -g -Iinc -Isub/fcm/inc -std=c++17
# Add -MMD -MP flags to generate dependency files
CXXFLAGS += -MMD -MP

BUILD_DIR = build

# Framework source files
FCM_SRCS = sub/fcm/src/FcmAsyncInterfaceHandler.cpp \
           sub/fcm/src/FcmBaseComponent.cpp \
           sub/fcm/src/FcmDevice.cpp \
           sub/fcm/src/FcmFunctionalComponent.cpp \
           sub/fcm/src/FcmMessageQueue.cpp \
           sub/fcm/src/FcmTimerHandler.cpp \
           sub/fcm/src/FcmWorkerHandler.cpp

# Project source files
PROJECT_SRCS = main.cpp \
              src/DoorsControllingSystem.cpp \
              src/Administrator.cpp \
              src/BackendInterface.cpp \
              src/ConfigurationDatabase.cpp \
              src/DoorController.cpp \
              src/SensorHandler.cpp \
              src/SystemController.cpp

# Combined source files
SRCS = $(PROJECT_SRCS) $(FCM_SRCS)

# Object files
OBJS = $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(SRCS))

# Dependency files
DEPS = $(OBJS:.o=.d)

# Executable name
EXEC = DoorsControllingSystem

# Default rule
all: $(EXEC)

# Link the executable
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJS)

# Compile source files into object files
$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up generated files
clean:
	rm -rf $(BUILD_DIR) $(EXEC)

# Include dependency files
-include $(DEPS)

.PHONY: all clean