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

set(CMAKE_CXX_STANDARD_REQUIRED ON) 
set(CMAKE_CXX_EXTENSIONS ON)

set(CMAKE_BUILD_TYPE Debug)
set(PROJECT_SOURCE_DIR ../..)

# for xcode to create the folder structure
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMAKE")
set(SOURCE_FILES    main.cpp)
set(OPENGL_BACKEND_IMPL ${PROJECT_SOURCE_DIR}/service-implementation/graphics/opengl)
set(INPUT_BACKEND_IMPL ${PROJECT_SOURCE_DIR}/service-implementation/input/glfw)
set(RESOURCE_PROVIDER_BACKEND_IMPL ${PROJECT_SOURCE_DIR}/service-implementation/disk/osx)
set(ENGINE_IMPL ${PROJECT_SOURCE_DIR}/engine)
set(ASSETS ${PROJECT_SOURCE_DIR}/projects/assets)
set(SAMPLE_GAME ${PROJECT_SOURCE_DIR}/projects/sample-game)
# third party libs
set(GLM ${PROJECT_SOURCE_DIR}/third-party/glm)
set(RAPID_JSON ${PROJECT_SOURCE_DIR}/third-party/rapidjson)
set(STB ${PROJECT_SOURCE_DIR}/third-party/stb)
set(GLAD ${PROJECT_SOURCE_DIR}/third-party/glad)

message("")
message( STATUS "ENGINE_IMPL : " ${ENGINE_IMPL} )
message( STATUS "OPENGL_BACKEND_IMPL : " ${OPENGL_BACKEND_IMPL} )
message( STATUS "INPUT_BACKEND_IMPL : " ${INPUT_BACKEND_IMPL} )
message("")

# Suppress warnings of the deprecation of glut functions on macOS.
if(APPLE)
 add_definitions(-Wno-deprecated-declarations)
endif()

# Add -O0 to remove optimizations when using gcc
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DAPPLE -O0 --std=c++17")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")

# adding source files
file(GLOB SOURCE_FILES *.cpp)

# adding opengl backend source files
file(GLOB BACKEND_FILES ${OPENGL_BACKEND_IMPL}/*.cpp ${INPUT_BACKEND_IMPL}/*.cpp ${RESOURCE_PROVIDER_BACKEND_IMPL}/*.cpp)
list(APPEND SOURCE_FILES ${BACKEND_FILES}) 

# adding sample game source files
file(GLOB SAMPLE_GAME_FILES ${SAMPLE_GAME}/*.cpp ${SAMPLE_GAME}/view/*.cpp ${SAMPLE_GAME}/objects/*.cpp ${SAMPLE_GAME}/objects/particles/*.cpp)
list(APPEND SOURCE_FILES ${SAMPLE_GAME_FILES})

# adding engine source files
file (GLOB ENGINE_FILES ${ENGINE_IMPL}/core/*.cpp ${ENGINE_IMPL}/data/*.cpp ${ENGINE_IMPL}/event/*.cpp ${ENGINE_IMPL}/platform/*.cpp ${ENGINE_IMPL}/utils/*.cpp ${ENGINE_IMPL}/view/*.cpp)
list(APPEND SOURCE_FILES ${ENGINE_FILES}) 

# adding third-party deps source code
# glm
file(GLOB GLM_CODE CONFIGURE_DEPENDS ${GLM}/*.h ${GLM}/*.hpp ${GLM}/*.inl)
list(APPEND SOURCE_FILES ${GLM_CODE}) 

# stb
list(APPEND SOURCE_FILES ${STB}/stb_image.h)

# glad
file(GLOB GLAD_HEADERS CONFIGURE_DEPENDS ${GLAD}/includes/*.h ${GLAD}/includes/*.hpp)
list(APPEND SOURCE_FILES ${GLAD}/glad.c)
list(APPEND SOURCE_FILES ${GLAD_HEADERS})

# message(SOURCE_FILES="${SOURCE_FILES}")

# create the xcode project with the folder structure
source_group(TREE "${PROJECT_SOURCE_DIR}/../" PREFIX "Source Files" FILES ${SOURCE_FILES})

# Find the packages we need.
find_package(GLFW3 REQUIRED)
find_package(OpenGL REQUIRED)

# adding code to the executable
add_executable(simple-2d-engine-opengl ${SOURCE_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "simple-2d-engine-opengl")

# copy assets to build directory
add_custom_target(copy_assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/../assets ${CMAKE_CURRENT_BINARY_DIR}/assets
)
add_dependencies(simple-2d-engine-opengl copy_assets)
set_target_properties(${PROJECT_NAME} PROPERTIES XCODE_GENERATE_SCHEME TRUE XCODE_SCHEME_WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/../)


# include
include_directories(${CMAKE_RUNTIME_OUTPUT_DIRECTORY} ${GLM} ${RAPID_JSON}/include/ ${ENGINE_IMPL} ${OPENGL_BACKEND_IMPL} ${RESOURCE_PROVIDER_BACKEND_IMPL}  ${OPENGL_INCLUDE_DIR} ${INPUT_BACKEND_IMPL} ${GLUT_INCLUDE_DIR} ${SAMPLE_GAME} ${STB} ${GLAD}/includes ${GLFW3_INCLUDE_DIR})
# link
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLFW3_LIBRARY} "-framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo")