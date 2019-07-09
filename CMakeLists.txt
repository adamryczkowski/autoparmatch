cmake_minimum_required(VERSION 3.13)

project(test_autoparmatch)

find_package(Boost)

if(EXISTS ../beetroot)
include(beetroot/cmake/beetroot.cmake)
build_target(NAMED_CALL_EXAMPLE_EXEC
	CALL_BY_POSITION
)

build_target(NAMED_CALL_EXAMPLE_EXEC
	CALL_BY_NAME
)

build_target(NAMED_CALL_EXAMPLE_EXEC
	CALL_BY_NAME CALL_BY_POSITION
)

finalize()
else()


set(CALL_BY_NAME 1 CACHE BOOL "Should I build call-by-name? (Needs Boost::Hana in called function)")
set(CALL_BY_POSITION 1 CACHE BOOL "Should I build call-by-position? (Does not need Boost::Hana in called function, compatible with nvcc)")
set(USE_CUDA 0 CACHE BOOL "Should I use CUDA?")

add_executable(test "test.cpp")
add_library(libtest "functions.cpp")
if(USE_CUDA)
	set_property(SOURCE functions.cpp PROPERTY LANGUAGE CUDA)
else()
	set_property(SOURCE functions.cpp PROPERTY LANGUAGE CXX)
endif()
if(CALL_BY_NAME)
	target_compile_definitions(libtest PRIVATE "NAMED")
	target_compile_definitions(test PRIVATE "NAMED")
	target_compile_features(libtest PUBLIC cxx_std_14)
	target_link_libraries(libtest Boost::boost)
	target_compile_definitions(libtest PRIVATE "BOOST_HANA_CONFIG_ENABLE_STRING_UDL")
else()
	target_compile_features(libtest PUBLIC cxx_std_11)
endif()
target_compile_features(test PRIVATE cxx_std_14)
if(CALL_BY_POSITION)
	target_compile_definitions(libtest PRIVATE "POSITIONAL")
	target_compile_definitions(test PRIVATE "POSITIONAL")
endif()
target_include_directories(libtest PRIVATE include)
target_include_directories(test PRIVATE include)
target_link_libraries(test Boost::boost)
target_link_libraries(test libtest)
target_compile_definitions(test PRIVATE "BOOST_HANA_CONFIG_ENABLE_STRING_UDL")


endif()
