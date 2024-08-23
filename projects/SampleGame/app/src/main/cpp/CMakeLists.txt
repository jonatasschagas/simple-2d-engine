# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.22.1)

# Declares and names the project.

project("samplegame")

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

set(PROJECT_SOURCE_DIR ../../../../../..)
set(OPENGL_BACKEND_IMPL ${PROJECT_SOURCE_DIR}/service-implementation/graphics/opengl)
set(INPUT_BACKEND_IMPL ${PROJECT_SOURCE_DIR}/service-implementation/input/android)
set(RESOURCE_PROVIDER_IMPL ${PROJECT_SOURCE_DIR}/service-implementation/disk/android)
set(ENGINE_IMPL ${PROJECT_SOURCE_DIR}/engine)
set(UTILS_IMPL ${PROJECT_SOURCE_DIR}/service-implementation/utils/android)
set(ASSETS ${PROJECT_SOURCE_DIR}/projects/assets)
set(SAMPLE_GAME ${PROJECT_SOURCE_DIR}/projects/sample-game)

# third party libs
set(GLM ${PROJECT_SOURCE_DIR}/third-party/glm)
set(STB ${PROJECT_SOURCE_DIR}/third-party/stb)

# adding source files
set(SOURCE_FILES    main.cpp)
file(GLOB_RECURSE SOURCE_FILES *.cpp)
file(GLOB_RECURSE
        OTHER_MODULES_SOURCE_FILES
        ${UTILS_IMPL}/*.cpp
        ${OPENGL_BACKEND_IMPL}/*.cpp
        ${RESOURCE_PROVIDER_IMPL}/*.cpp
        ${INPUT_BACKEND_IMPL}/*.cpp
        ${ENGINE_IMPL}/*.cpp
        ${SAMPLE_GAME}/*.cpp
        )
list(APPEND SOURCE_FILES ${OTHER_MODULES_SOURCE_FILES})

# adding third-party deps source code
file(GLOB_RECURSE GLM_CODE ${GLM}/*.h ${GLM}/*.hpp ${GLM}/*.inl)
list(APPEND SOURCE_FILES ${GLM_CODE})
list(APPEND SOURCE_FILES ${STB}/stb_image.h)

add_library( # Sets the name of the library.
        samplegame

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        ${SOURCE_FILES}
        )

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)

# Searches for a package provided by the game activity dependency

find_package(game-activity REQUIRED CONFIG)

# include
include_directories(${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
        ${GLM}
        ${RESOURCE_PROVIDER_IMPL}
        ${ENGINE_IMPL}
        ${UTILS_IMPL}
        ${INPUT_BACKEND_IMPL}
        ${OPENGL_BACKEND_IMPL}
        ${SAMPLE_GAME}
        ${STB})


# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
        samplegame

        android

        # The game activity
        game-activity::game-activity

        # EGL, required for configuring the display context
        EGL

        # GL ES 3, used for the sample renderer
        GLESv3

        # for AImageDecoder, to load images from resources
        jnigraphics

        # Links the target library to the log library
        # included in the NDK.
        ${log-lib})