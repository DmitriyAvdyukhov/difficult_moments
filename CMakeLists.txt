cmake_minimum_required(VERSION 3.14)

project(difficult_moments)

set(CMAKE_EXPORT_COMPILE_COMMANDS On)

set(CMAKE_CXX_STANDARD 17)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)


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
				  src/dz7.h)
				  




 
include_directories(${Protobuf_INCLUDE_DIRS})

include_directories(${CMAKE_CURRENT_BINARY_DIR}) 
 
add_executable(main ${PROTO_SRCS} ${PROTO_HDRS} ${FILES_PROJECT}) 

target_link_libraries(main ${Protobuf_LIBRARIES}) 

target_include_directories(main PUBLIC ${CMAKE_CURRENT_BINARY_DIR})



