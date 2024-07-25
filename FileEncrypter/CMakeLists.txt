# CMakeList.txt : CMake project for CMakeTestWSL, include source and define
# project specific logic here.
#

# Add source to this project's executable.
project(FileEncrypter VERSION 1.0 DESCRIPTION "Easy terminal tool to encrypt with a password a file with RSA 64 bit")

file(GLOB_RECURSE source_list "src/*.cpp")
add_executable(${PROJECT_NAME} ${source_list})

# Release?
# set(CMAKE_BUILD_TYPE Release)

target_include_directories(${PROJECT_NAME} PRIVATE 
    #httplib
    "deps"
    "include"
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
