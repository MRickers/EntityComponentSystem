option(build_ecs_tests "" ON)

include(CTest)

if(build_ecs_tests )
message(STATUS "Building ecs tests")
add_executable(ecs_tests unittests/ecs_tests.cpp)
target_include_directories(ecs_tests PRIVATE ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/logging ${CMAKE_SOURCE_DIR}googletest/googletest/include ${BACKEND_INCLUDE})
target_link_libraries(ecs_tests PRIVATE GTest::gtest GTest::gtest_main ecslib)
install(TARGETS ecs_tests DESTINATION $<TARGET_FILE_DIR:timer_example>)
add_custom_command(TARGET ecs_tests POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:ecs_tests> $<TARGET_FILE_DIR:ecs_tests>
COMMAND_EXPAND_LISTS)

endif()