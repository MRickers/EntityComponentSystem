option(BUILD_EXAMPLES "" ON)

if(BUILD_EXAMPLES)
	message(STATUS "Building examples")

	add_executable(short_example examples/short_example.cpp)
	target_include_directories(
		short_example PRIVATE 
		${CMAKE_SOURCE_DIR}/backend/SFML-2.5.1-64bit/SFML-2.5.1/include
		${CMAKE_SOURCE_DIR}/include)
	target_link_libraries(short_example graphics system audio network window)
	# copies sfml dlls to runtime directory needs cmake 2.21
	add_custom_command(TARGET short_example POST_BUILD
	  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:short_example> $<TARGET_FILE_DIR:short_example>
	  COMMAND_EXPAND_LISTS
	  )
endif()