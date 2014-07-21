cmake_minimum_required(VERSION 3.0)
set (CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++")
include_directories ("/opt/local/include")
include_directories ("./TestKit")

# MKArgument Tests
set (T_MKArgument-src T_MKArgument.cpp)
add_executable (t_mkargument ${T_MKArgument-src})

# MKVector Tests
set (T_MKVector-src T_MKVector.cpp)
add_executable (t_mkvector ${T_MKVector-src})

# Nested MKVector Test
set (T_MKMatrix-src T_MKMatrix.cpp)
add_executable (t_mkmatrix ${T_MKMatrix-src})
