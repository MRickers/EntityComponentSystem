cmake_minimum_required(VERSION 3.10)
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
message("-- Linux build not implemented.")
endif()

add_compile_options(${COMPILE_OPTIONS})

add_library(ecslib SHARED ${PROJECT_SOURCE_DIR}/src/ecs/entity_manager.cpp)
target_include_directories(ecslib PRIVATE ${PROJECT_SOURCE_DIR}/include)
install(TARGETS ecslib DESTINATION bin)

add_subdirectory(googletest)
add_subdirectory(tests)
