cmake_minimum_required(VERSION 3.31.0)
project(HeliHero VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

message("Compiler: ${CMAKE_CXX_COMPILER_ID}")

# Abhängigkeiten
include(cmake/CPM.cmake)
include(cmake/warnings.cmake)

# raylib-cpp
CPMAddPackage(
    NAME raylib-cpp
    GITHUB_REPOSITORY RobLoach/raylib-cpp
    VERSION 5.0.2
)

# Raylib
find_package(raylib QUIET)
if(NOT raylib_FOUND)
    FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.0
    )
    FetchContent_MakeAvailable(raylib)
endif()

# Alle .cpp- und .hpp-Dateien rekursiv suchen
file(GLOB_RECURSE SOURCES
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/*.hpp"
)

# Executable erstellen
add_executable(${PROJECT_NAME} ${SOURCES})

# Include-Verzeichnisse
target_include_directories(${PROJECT_NAME} PRIVATE
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/include/raylib
    ${raylib_cpp_SOURCE_DIR}/include
    ${raylib_nuklear_SOURCE_DIR}/include
    ${nlohmann_json_SOURCE_DIR}/include
)

# Link-Bibliotheken
target_link_libraries(${PROJECT_NAME} PRIVATE
    raylib
)

# Assets kopieren
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
    COMMENT "Copying assets folder to binary directory"
)


# Debug/Release-Konfiguration
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/$<CONFIG>)
target_compile_options(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Debug>:-g -O0>
    $<$<CONFIG:Release>:-O3>
)