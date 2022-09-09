cmake_minimum_required(VERSION 3.0)

project(difficult_moments)
set(CMAKE_CXX_STANDARD 17)

set(FILES_PROJECT main.cpp 
                  dz1.h dz1.cpp 
				  )
				  
add_executable(main ${FILES_PROJECT})