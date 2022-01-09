cmake_minimum_required(VERSION 3.21)
project(ecs CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32)
# GS	- checks buffer security
# Gs	- Controles stack probes
# GT	- Using thread-local storage
# guard:cf	- Adds control flow guard security checks
set(COMPILE_OPTIONS /W4 /GT /GS /Gs /guard:cf /RTC1)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS 1)
include(InstallRequiredSystemLibraries)

elseif(UNIX)
message(STATUS "Linux build not implemented.")
endif()

add_compile_options(${COMPILE_OPTIONS})

option(BACKEND_SFML_64 "" ON)

if(BACKEND_SFML_64)
message(STATUS "Building with backend SFML-2.5.1-64bit")
add_compile_definitions(BACKEND_SFML)
include("backend_sfml.cmake")
endif()

add_subdirectory(Vector)


# ecslib
add_library(ecslib SHARED 
src/ecs/core/entity_manager.cpp 
src/ecs/utils/timer.cpp
src/ecs/systems/render_system.cpp
src/ecs/systems/physics_system.cpp
${BACKEND_SOURCES}
)
target_include_directories(
ecslib PRIVATE 
${PROJECT_SOURCE_DIR}/include
${BACKEND_INCLUDE})
target_link_libraries(ecslib vector audio graphics system window network)
install(TARGETS ecslib DESTINATION bin)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_subdirectory(googletest)
add_subdirectory(tests)
add_subdirectory(src)

