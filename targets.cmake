set(ENUM_TEMPLATES NAMED_CALL_EXAMPLE_LIB NAMED_CALL_EXAMPLE_EXEC)

set(TARGET_PARAMETERS 
	CALL_BY_NAME	OPTION	BOOL	0
	CALL_BY_POSITION	OPTION	BOOL	0
	USE_GPU	OPTION	BOOL	0
)

function(declare_dependencies TEMPLATE_NAME)
	if("${TEMPLATE_NAME}" STREQUAL "NAMED_CALL_EXAMPLE_EXEC")
		build_target(MAKE_FUNCTION_CALL)
		build_target(NAMED_CALL_EXAMPLE_LIB)
	else()
		if(CALL_BY_NAME)
			build_target(BE_CALLED_BY_NAME)
		endif()
	endif()
endfunction()

function(generate_targets TARGET_NAME TEMPLATE_NAME)
	set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
	if("${TEMPLATE_NAME}" STREQUAL "NAMED_CALL_EXAMPLE_EXEC")
		add_executable(${TARGET_NAME} "${SOURCE_DIR}/test.cpp")
	else()
		add_library(${TARGET_NAME} "${SOURCE_DIR}/functions.cpp")
		if(USE_GPU)
			set_property(SOURCE ${SOURCE_DIR}/functions.cpp PROPERTY LANGUAGE CUDA)
		else()
			set_property(SOURCE ${SOURCE_DIR}/functions.cpp PROPERTY LANGUAGE CXX)
		endif()
		if(NOT CALL_BY_NAME)
			target_compile_features(${TARGET_NAME} INTERFACE cxx_std_11)
		endif()
	endif()
	if(CALL_BY_NAME)
		target_compile_definitions(${TARGET_NAME} PRIVATE "NAMED")
	endif()
	if(CALL_BY_POSITION)
		target_compile_definitions(${TARGET_NAME} PRIVATE "POSITIONAL")
	endif()
	target_include_directories(${TARGET_NAME} PRIVATE "${SOURCE_DIR}/include")
	
endfunction()

