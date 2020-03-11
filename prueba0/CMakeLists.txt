
cmake_minimum_required(VERSION 2.8.12)

project("generated_code")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find requirements
find_package(fastcdr REQUIRED)
find_package(fastrtps REQUIRED)


message(STATUS "Configuring cadena...")
add_library(cadena_lib cadena.cxx)
target_link_libraries(cadena_lib fastcdr fastrtps)

add_executable(cadena cadenaPubSubTypes.cxx cadenaPublisher.cxx cadenaSubscriber.cxx cadenaPubSubMain.cxx)
target_link_libraries(cadena fastcdr fastrtps  cadena_lib )



