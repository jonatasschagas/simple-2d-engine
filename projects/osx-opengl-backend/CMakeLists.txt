cmake_minimum_required(VERSION 3.13.1)

message("")
message( STATUS "CMAKE_BINARY_DIR: " ${CMAKE_BINARY_DIR} )
message( STATUS "CMAKE_SOURCE_DIR: " ${CMAKE_SOURCE_DIR} )
message( STATUS "CMAKE_COMMAND: " ${CMAKE_COMMAND} )
message( STATUS "CMAKE_VERSION: " ${CMAKE_VERSION} )
message( STATUS "CMAKE_C_COMPILER: " ${CMAKE_C_COMPILER} )
message( STATUS "CMAKE_PROJECT_NAME: " ${CMAKE_PROJECT_NAME} )
message( STATUS "CMAKE_FINDCMAKE: " ${CMAKE_SOURCE_DIR}/CMAKE )

project(simple-2d-engine-opengl)

set(CMAKE_C_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON) 
set(CMAKE_CXX_EXTENSIONS ON)

set(CMAKE_BUILD_TYPE Debug)
set(PROJECT_SOURCE_DIR ../..)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMAKE")
set(SOURCE_FILES    main.cpp)
set(OPENGL_BACKEND_IMPL ${PROJECT_SOURCE_DIR}/opengl-backend)
set(ENGINE_IMPL ${PROJECT_SOURCE_DIR}/engine)
set(ASSETS ${PROJECT_SOURCE_DIR}/projects/assets)
set(GLM ${PROJECT_SOURCE_DIR}/third-party/glm)
set(RAPID_JSON ${PROJECT_SOURCE_DIR}/third-party/rapidjson)
set(SAMPLE_GAME ${PROJECT_SOURCE_DIR}/projects/sample-game)

message("")
message( STATUS "ENGINE_IMPL : " ${ENGINE_IMPL} )
message( STATUS "OPENGL_BACKEND_IMPL : " ${OPENGL_BACKEND_IMPL} )
message("")

# Suppress warnings of the deprecation of glut functions on macOS.
if(APPLE)
 add_definitions(-Wno-deprecated-declarations)
endif()

# Add -O0 to remove optimizations when using gcc
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 --std=c++14")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")

# adding source files
file(GLOB_RECURSE SOURCE_FILES *.cpp)
file(GLOB_RECURSE OTHER_MODULES_SOURCE_FILES ${OPENGL_BACKEND_IMPL}/*.cpp ${ENGINE_IMPL}/*.cpp ${SAMPLE_GAME}/*.cpp)
list(APPEND SOURCE_FILES ${OTHER_MODULES_SOURCE_FILES}) 

# adding third-party deps source code
file(GLOB_RECURSE GLM_CODE ${GLM}/*.h ${GLM}/*.hpp ${GLM}/*.inl)
file(GLOB_RECURSE RAPID_JSON_CODE ${RAPID_JSON}/include/*.h ${RAPID_JSON}/include/*.hpp)
list(APPEND SOURCE_FILES ${GLM_CODE}) 
list(APPEND SOURCE_FILES ${RAPID_JSON_CODE})

# Find the packages we need.
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

# adding code to the executable
add_executable(simple-2d-engine-opengl ${SOURCE_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "simple-2d-engine-opengl")

# copy assets to build directory
add_custom_target(copy_assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/../assets ${CMAKE_CURRENT_BINARY_DIR}/assets
)
add_dependencies(simple-2d-engine-opengl copy_assets)

# include
include_directories(${CMAKE_RUNTIME_OUTPUT_DIRECTORY} ${GLM} ${RAPID_JSON}/include/ ${ENGINE_IMPL} ${OPENGL_BACKEND_IMPL} ${OPENGL_INCLUDE_DIR} ${GLUT_INCLUDE_DIR} ${SAMPLE_GAME})
# link
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})