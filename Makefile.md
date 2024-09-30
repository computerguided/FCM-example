# Explaination of the Makefile

The [Makefile](Makefile) is designed to automate the build process for a C++ project. Let's break down each part of the Makefile in detail:

### 1. **Compiler**
```makefile
CXX = g++
```
- `CXX`: This is the variable for the C++ compiler being used, in this case, `g++`. This variable is used later in the commands to specify which compiler to use.

### 2. **Compiler Flags**
```makefile
CXXFLAGS = -Wall -g -Iinc -Isub/fcm/inc -std=c++17
```
- `CXXFLAGS`: These are the flags passed to the compiler when compiling the source code. The flags here are:
  - `-Wall`: Enable all compiler warnings to help catch potential issues.
  - `-g`: Generate debugging information to allow debugging tools (like `gdb`) to be used on the compiled code.
  - `-Iinc`: Add `inc/` directory to the include path for header files.
  - `-Isub/fcm/inc`: Add `sub/fcm/inc/` directory to the include path for header files.
  - `-std=c++17`: Specifies that the C++17 standard should be used for compilation.

### 3. **Directories and Source Files**
```makefile
BUILD_DIR = build
```
- `BUILD_DIR`: Specifies where the compiled object files will be placed. The object files will be placed in the `build/` directory.

#### Framework Source Files
```makefile
FCM_SRCS = sub/fcm/src/FcmAsyncInterfaceHandler.cpp \
           sub/fcm/src/FcmBaseComponent.cpp \
           sub/fcm/src/FcmDevice.cpp \
           sub/fcm/src/FcmFunctionalComponent.cpp \
           sub/fcm/src/FcmMessageQueue.cpp \
           sub/fcm/src/FcmTimerHandler.cpp
```
- `FCM_SRCS`: Lists the source files for a framework or module named `FCM`, located in `sub/fcm/src/`.

#### Project Source Files
```makefile
PROJECT_SRCS = main.cpp \
               src/DoorsControllingSystem.cpp \
               src/Administrator.cpp \
               src/BackendInterface.cpp \
               src/ConfigurationDatabase.cpp \
               src/DoorController.cpp \
               src/SensorHandler.cpp \
               src/SystemController.cpp
```
- `PROJECT_SRCS`: Lists the project's main source files, which are located in the `src/` directory and the `main.cpp` file in the root directory.

### 4. **Combining Source Files**
```makefile
SRCS = $(PROJECT_SRCS) $(FCM_SRCS)
```
- `SRCS`: Combines all project source files (`PROJECT_SRCS`) and the framework source files (`FCM_SRCS`) into a single list of source files.

### 5. **Object Files**
```makefile
OBJS = $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(SRCS))
```
- `OBJS`: This generates a list of object files corresponding to each source file in `SRCS`.
  - `patsubst`: This function transforms each `.cpp` file in `SRCS` into an object file (`.o`), and places the resulting object files in the `build/` directory.

### 6. **Executable Name**
```makefile
EXEC = DoorsControllingSystem
```
- `EXEC`: The name of the final executable that will be created after linking the object files.

### 7. **Default Rule: `all`**
```makefile
all: $(EXEC)
```
- The `all` target is the default rule. When you run `make` without specifying a target, this rule will be executed.
- It depends on the `$(EXEC)` target, so it will first build the executable by linking the object files.

### 8. **Link the Executable**
```makefile
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJS)
```
- This rule builds the executable. It depends on the object files (`$(OBJS)`).
- The command to be executed is `$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJS)`, which tells the compiler to link the object files into a final executable named `$(EXEC)`.

### 9. **Compile Source Files into Object Files**
```makefile
$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@
```
- This rule specifies how to compile individual source files (`%.cpp`) into object files (`%.o`).
- `@mkdir -p $(dir $@)`: This creates the necessary directories in `build/` if they don't already exist (the `-p` flag prevents errors if the directory already exists).
- `$(CXX) $(CXXFLAGS) -c $< -o $@`: This invokes the compiler to compile the source file (`$<` refers to the source file, e.g., `main.cpp`) into the corresponding object file (`$@`).

### 10. **Clean Rule**
```makefile
clean:
	rm -rf $(BUILD_DIR) $(EXEC)
```
- This rule defines the `clean` target. When you run `make clean`, it will remove the `build/` directory and the final executable (`$(EXEC)`), cleaning up all generated files.

### 11. **Phony Targets**
```makefile
.PHONY: all clean
```
- `.PHONY`: Declares `all` and `clean` as "phony" targets, meaning they are not actual files. This is important because it prevents conflicts if a file named `all` or `clean` were to exist in the directory.

### Summary:
- This Makefile automates the process of compiling the C++ project.
- It compiles the source files (`SRCS`) into object files (`OBJS`), then links them into an executable named `DoorsControllingSystem`.
- You can run `make` to build the project, `make clean` to clean up, and the object files are neatly stored in the `build/` directory.
