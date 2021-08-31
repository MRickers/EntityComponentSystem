option(build_ecs_tests ON)

include(CTest)

if(build_ecs_tests )
message("-- building ecs tests")
add_executable(ecs_tests unittests/ecs_tests.cpp ${CMAKE_SOURCE_DIR}/src/ecs/entity_manager.cpp)
target_include_directories(ecs_tests PRIVATE ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/logging ${CMAKE_SOURCE_DIR}googletest/googletest/include)
target_link_libraries(ecs_tests PRIVATE GTest::gtest GTest::gtest_main)
install(TARGETS ecs_tests DESTINATION bin)

endif()