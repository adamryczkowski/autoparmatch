set(ENUM_TEMPLATES MAKE_FUNCTION_CALL BE_CALLED_BY_NAME)

set(LINK_PARAMETERS 
	LOG_LEVEL	SCALAR	"CHOICE(trace:debug:warning:error)" warning
)

#set(FLOAT_PRECISION CUDA_ARCH MAX_VECTOR_SIZE) #What parameters of the dependency our clients are allowed to modify

function(declare_dependencies TEMPLATE_NAME)
	build_target(Boost::boost VERSION 1.67.0)
endfunction()

function(generate_targets TARGET_NAME TEMPLATE_NAME)
	set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
	add_library(${TARGET_NAME} INTERFACE)
	if("${TEMPLATE_NAME}" STREQUAL "MAKE_FUNCTION_CALL")
		target_sources(${TARGET_NAME} 
			INTERFACE
				${SOURCE_DIR}/include/make_function_call.h
		)
	else()
		target_sources(${TARGET_NAME} 
			INTERFACE
				${SOURCE_DIR}/include/be_called_by_name.h
		)
	endif()
	target_compile_features(${TARGET_NAME} INTERFACE cxx_std_14)
	target_compile_definitions(${TARGET_NAME} INTERFACE "BOOST_HANA_CONFIG_ENABLE_STRING_UDL")
	target_include_directories(${TARGET_NAME} INTERFACE "${SOURCE_DIR}/include")
endfunction()

