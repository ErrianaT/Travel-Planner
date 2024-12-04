Group Members: Isabel Donner, Sofia Cruz, Erriana Thomas

Notes: 

To run the code, please install SFML using the following 
lines of code in the CMakeLists.txt file in CLion:

cmake_minimum_required(VERSION 3.29)
project(Travel_Planner LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Configure output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Add the Travel_Planner executable
add_executable(Travel_Planner
        src/B-Tree.cpp
        src/B-Tree.h
        src/main.cpp
        src/TempMap.h
        src/B-Tree.h
        src/B-Tree.h
)

# Include and fetch SFML
include(FetchContent)
FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM
)
FetchContent_MakeAvailable(SFML)

# Link SFML to Travel_Planner
target_link_libraries(Travel_Planner PRIVATE sfml-graphics)
target_compile_features(Travel_Planner PRIVATE cxx_std_17)

# Special handling for Windows
if(WIN32)
    add_custom_command(
            TARGET Travel_Planner
            COMMENT "Copy OpenAL DLL"
            PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy
            ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll
            $<TARGET_FILE_DIR:Travel_Planner>
            VERBATIM
    )
endif()