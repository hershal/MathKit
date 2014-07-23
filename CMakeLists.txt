cmake_minimum_required(VERSION 3.0)
set (CMAKE_CXX_FLAGS "-std=c++1y -stdlib=libc++")
include_directories ("/opt/local/include")
include_directories ("./TestKit")
include_directories ("./FloatLib")
add_subdirectory (./FloatLib floatlib)

# MKArgument Tests
set (T_MKArgument-src T_MKArgument.cpp)
add_executable (t_mkargument ${T_MKArgument-src})

# MKVector Tests
set (T_MKVector-src T_MKVector.cpp)
add_executable (t_mkvector ${T_MKVector-src})

# Nested MKVector Tests
set (T_MKMatrix-src T_MKMatrix.cpp)
add_executable (t_mkmatrix ${T_MKMatrix-src})

# MKGaussElim Tests
set (T_MKGaussElim-src T_MKGaussElim.cpp MKGaussElim.cpp)
add_executable (t_mkgausselim ${T_MKGaussElim-src})
target_link_libraries (t_mkgausselim floatlib)
