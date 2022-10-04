cmake_minimum_required(VERSION 3.14)

project(difficult_moments)
#enable_testing()

set(CMAKE_EXPORT_COMPILE_COMMANDS On)

set(CMAKE_CXX_STANDARD 17)

set (TARGET main)
 
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

find_package(Threads REQUIRED)

find_package(Protobuf REQUIRED)

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS src/person.proto)

set(FILES_PROJECT src/main.cpp 
				  src/log_duration.h
                  src/dz1.h src/dz1.cpp 
				  src/dz2.h
				  src/dz3.h
				  src/dz4_5.h src/dz4_5.cpp
				  src/dz6.h
				  src/person.proto
				  src/dz7.h src/dz7.cpp)

include_directories(${Protobuf_INCLUDE_DIRS})

include_directories(${CMAKE_CURRENT_BINARY_DIR}) 

include_directories("${CMAKE_SOURCE_DIR}/googletest/include")
 
add_executable(${TARGET} ${PROTO_SRCS} ${PROTO_HDRS} ${FILES_PROJECT}) 

target_link_libraries(${TARGET} ${Protobuf_LIBRARIES}) 

target_include_directories(${TARGET} PUBLIC ${CMAKE_CURRENT_BINARY_DIR})



