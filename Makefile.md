# Detailed Makefile Explanation

## 1. Compiler and Flag Setup
```makefile
CXX = g++
CXXFLAGS = -Wall -g -Iinc -Isub/fcm/inc -std=c++17
CXXFLAGS += -MMD -MP
```
- `CXX = g++`: Defines the C++ compiler to use
- `CXXFLAGS` contains all compiler flags:
  - `-Wall`: Enable all common warning messages
  - `-g`: Include debugging information in the executable
  - `-Iinc`: Add 'inc' directory to the include search path
  - `-Isub/fcm/inc`: Add 'sub/fcm/inc' directory to the include search path
  - `-std=c++17`: Use C++17 standard
  - `-MMD`: Generate dependency files (.d) for each source file
  - `-MP`: Create phony targets for each dependency to prevent errors if headers are deleted

## 2. Directory Structure
```makefile
BUILD_DIR = build
```
- Defines a build directory to store all generated files
- Keeps the source directories clean by separating compiled objects

## 3. Source Files Organization
```makefile
FCM_SRCS = sub/fcm/src/FcmAsyncInterfaceHandler.cpp \
           sub/fcm/src/FcmBaseComponent.cpp \
           # ... other FCM sources

PROJECT_SRCS = main.cpp \
              src/DoorsControllingSystem.cpp \
              # ... other project sources

SRCS = $(PROJECT_SRCS) $(FCM_SRCS)
```
- `FCM_SRCS`: Lists all framework component source files
- `PROJECT_SRCS`: Lists all project-specific source files
- `SRCS`: Combines both lists into a single variable
- Using separate variables makes it easier to manage different parts of the project

## 4. Object and Dependency Files
```makefile
OBJS = $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(SRCS))
DEPS = $(OBJS:.o=.d)
```
- `OBJS`: Generates list of object file paths
  - `patsubst` function replaces .cpp extensions with .o
  - Prepends BUILD_DIR to maintain directory structure
  - Example: `src/DoorController.cpp` → `build/src/DoorController.o`
- `DEPS`: Creates list of dependency files by replacing .o with .d
  - Example: `build/src/DoorController.o` → `build/src/DoorController.d`

## 5. Main Target and Rules
```makefile
EXEC = DoorsControllingSystem

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJS)
```
- `EXEC`: Defines the final executable name
- `all`: Default target that builds the executable
- `$(EXEC)`: Rule to link object files into final executable
  - Depends on all object files (`$(OBJS)`)
  - Links using g++ with specified flags

## 6. Compilation Rule
```makefile
$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@
```
- Pattern rule for creating object files:
  - Target: `$(BUILD_DIR)/%.o` (object file in build directory)
  - Prerequisite: `%.cpp` (corresponding source file)
  - `@mkdir -p $(dir $@)`: Creates necessary subdirectories
    - `$@` is the target name (the .o file)
    - `$(dir ...)` extracts the directory part
  - Compilation command breaks down as:
    - `$(CXX)`: The compiler (g++)
    - `$(CXXFLAGS)`: All compiler flags
    - `-c`: Compile only, don't link
    - `$<`: The prerequisite (the .cpp file)
    - `-o $@`: Output to the target (.o file)

## 7. Dependency Handling
```makefile
-include $(DEPS)
```
- Includes all generated dependency files
- The `-` prefix tells make to not error if files don't exist
- Each .d file contains:
  - The object file's dependencies on headers
  - Phony targets for each header (thanks to -MP)
  - Example content of a .d file:
    ```makefile
    build/src/DoorController.o: src/DoorController.cpp inc/DoorController.h \
                               inc/CommonTypes.h
    inc/DoorController.h:
    inc/CommonTypes.h:
    ```

## 8. Cleanup
```makefile
clean:
	rm -rf $(BUILD_DIR) $(EXEC)

.PHONY: all clean
```
- `clean`: Removes all generated files
  - Deletes build directory and executable
- `.PHONY`: Declares targets that don't create files
  - Prevents conflicts with files named 'all' or 'clean'

## Dependency Chain Example
When you modify a header file, here's how the rebuild process works:

1. You modify `inc/DoorController.h`
2. Make reads the dependency files
3. It finds that `build/src/DoorController.o` depends on `inc/DoorController.h`
4. The object file is rebuilt because its dependency changed
5. Make then rebuilds the executable because an object file changed

The `-MMD` flag ensures this happens automatically by:
1. Scanning included headers during compilation
2. Writing dependencies to `.d` files
3. Including these dependencies in the makefile for the next run
