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

add_library(ecslib SHARED src/ecs/core/entity_manager.cpp "include/ecs/systems/render_sfml.h")
target_include_directories(ecslib PRIVATE ${PROJECT_SOURCE_DIR}/include)
install(TARGETS ecslib DESTINATION bin)

option(BACKEND_SFML_64 "" ON)

if(BACKEND_SFML_64)
message(STATUS "building with backend SFML-2.5.1-64bit")
add_compile_definitions(BACKEND_SFML)

add_library(audio SHARED IMPORTED)
set_property(TARGET audio PROPERTY
             IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/backend/SFML-2.5.1-64bit/SFML-2.5.1/bin/sfml-audio-2.dll)
set_property(TARGET audio PROPERTY
             IMPORTED_IMPLIB ${CMAKE_SOURCE_DIR}/backend/SFML-2.5.1-64bit/SFML-2.5.1/lib/sfml-audio.lib)

add_library(graphics SHARED IMPORTED)
set_property(TARGET graphics PROPERTY
             IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/backend/SFML-2.5.1-64bit/SFML-2.5.1/bin/sfml-graphics-2.dll)
set_property(TARGET graphics PROPERTY
             IMPORTED_IMPLIB ${CMAKE_SOURCE_DIR}/backend/SFML-2.5.1-64bit/SFML-2.5.1/lib/sfml-graphics.lib)

add_library(network SHARED IMPORTED)
set_property(TARGET network PROPERTY
             IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/backend/SFML-2.5.1-64bit/SFML-2.5.1/bin/sfml-network-2.dll)
set_property(TARGET network PROPERTY
             IMPORTED_IMPLIB ${CMAKE_SOURCE_DIR}/backend/SFML-2.5.1-64bit/SFML-2.5.1/lib/sfml-network.lib)

add_library(system SHARED IMPORTED)
set_property(TARGET system PROPERTY
             IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/backend/SFML-2.5.1-64bit/SFML-2.5.1/bin/sfml-system-2.dll)
set_property(TARGET system PROPERTY
             IMPORTED_IMPLIB ${CMAKE_SOURCE_DIR}/backend/SFML-2.5.1-64bit/SFML-2.5.1/lib/sfml-system.lib)

add_library(window SHARED IMPORTED)
set_property(TARGET window PROPERTY
             IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/backend/SFML-2.5.1-64bit/SFML-2.5.1/bin/sfml-window-2.dll)
set_property(TARGET window PROPERTY
             IMPORTED_IMPLIB ${CMAKE_SOURCE_DIR}/backend/SFML-2.5.1-64bit/SFML-2.5.1/lib/sfml-window.lib)
endif()



add_subdirectory(Vector)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_subdirectory(googletest)
add_subdirectory(tests)
add_subdirectory(src)

