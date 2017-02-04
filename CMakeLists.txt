
cmake_minimum_required (VERSION 2.8.11)
project (Project_Worm)

set(GLM_ROOT "deps/glm" CACHE FILEPATH "GLM root path")
set(SFML_ROOT "deps/SFML-2.4.1" CACHE FILEPATH "SFML root path")

set(SRCFILES src/Project_Worm.cpp src/Mesh.cpp src/Vertex.cpp src/MeshView.cpp)
set(EXTFILES src/gl3w.c)

list(APPEND CMAKE_CXX_FLAGS "-std=c++17 -Wall -Wfatal-errors")
#add_subdirectory (Hello)
#add_subdirectory (Demo)
#add_library (Hello hello.cxx)
add_executable (Project_Worm ${SRCFILES} ${EXTFILES})

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(Project_Worm ${SFML_LIBRARIES})
endif()

target_include_directories (Project_Worm PUBLIC src)
target_include_directories (Project_Worm PUBLIC includes)
target_include_directories (Project_Worm PUBLIC ${GLM_ROOT})
target_link_libraries (Project_Worm opengl32)