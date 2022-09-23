cmake_minimum_required(VERSION 3.0)

project(difficult_moments)
set(CMAKE_CXX_STANDARD 17)

set(FILES_PROJECT main.cpp 
				  log_duration.h
                  dz1.h dz1.cpp 
				  dz2.h
				  dz3.h
				  dz4_5.h)
				  
add_executable(main ${FILES_PROJECT})