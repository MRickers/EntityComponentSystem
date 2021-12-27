option(BUILD_EXAMPLES "" ON)

if(BUILD_EXAMPLES)
	message(STATUS "Building examples")
	message(STATUS "Building sfml example")
	add_executable(short_example examples/short_example.cpp)
	target_include_directories(
		short_example PRIVATE 
		${BACKEND_INCLUDE}
		${CMAKE_SOURCE_DIR}/include)
	target_link_libraries(short_example graphics system audio network window)
	# copies sfml dlls to runtime directory, needs cmake 2.21
	add_custom_command(TARGET short_example POST_BUILD
	  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:short_example> $<TARGET_FILE_DIR:short_example>
	  COMMAND_EXPAND_LISTS
	  )

	find_package(Threads)
	message(STATUS "Building timer example")
	add_executable(timer_example examples/timer_example.cpp)
	target_include_directories(
		timer_example PRIVATE
		${CMAKE_SOURCE_DIR}/include
	)
	target_link_libraries(timer_example ecslib Threads::Threads)
	install(TARGETS timer_example DESTINATION bin)

	message(STATUS "Building cube example")
	add_executable(cube_example examples/cube_example.cpp)
	target_include_directories(cube_example PRIVATE ${CMAKE_SOURCE_DIR}/include ${BACKEND_INCLUDE})
	target_link_libraries(cube_example ecslib)

	
endif()