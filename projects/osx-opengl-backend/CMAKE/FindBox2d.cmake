FIND_PATH(box2d_INCLUDE_DIR box2d.h
        HINTS
        ${box2d}
        $ENV{box2d}
        PATH_SUFFIXES include/box2d include box2d
        i686-w64-mingw32/include/box2d
        x86_64-w64-mingw32/include/box2d
        PATHS
        ~/Library/Frameworks
        /Library/Frameworks
        /usr/local/include/box2d
        /usr/include/box2d
        /sw # Fink
        /opt/local # DarwinPorts
        /opt/csw # Blastwave
        /opt
        )

# Lookup the 64 bit libs on x64
IF(CMAKE_SIZEOF_VOID_P EQUAL 8)
    FIND_LIBRARY(box2d_LIBRARY_TEMP box2d
            HINTS
            ${box2d}
            $ENV{box2d}
            PATH_SUFFIXES lib64 lib
            lib/x64
            x86_64-w64-mingw32/lib
            PATHS
            /sw
            /opt/local
            /opt/csw
            /opt
            )
    # On 32bit build find the 32bit libs
ELSE(CMAKE_SIZEOF_VOID_P EQUAL 8)
    FIND_LIBRARY(box2d_LIBRARY_TEMP box2d
            HINTS
            ${box2d}
            $ENV{box2d}
            PATH_SUFFIXES lib
            lib/x86
            i686-w64-mingw32/lib
            PATHS
            /sw
            /opt/local
            /opt/csw
            /opt
            )
ENDIF(CMAKE_SIZEOF_VOID_P EQUAL 8)

IF(NOT box2d_BUILDING_LIBRARY)
    IF(NOT ${box2d_INCLUDE_DIR} MATCHES ".framework")
        # Non-OS X framework versions expect you to also dynamically link to
        # box2dmain. This is mainly for Windows and OS X. Other (Unix) platforms
        # seem to provide box2dmain for compatibility even though they don't
        # necessarily need it.
        # Lookup the 64 bit libs on x64
        IF(CMAKE_SIZEOF_VOID_P EQUAL 8)
            FIND_LIBRARY(box2dMAIN_LIBRARY
                    NAMES box2dmain
                    HINTS
                    ${box2d}
                    $ENV{box2d}
                    PATH_SUFFIXES lib64 lib
                    lib/x64
                    x86_64-w64-mingw32/lib
                    PATHS
                    /sw
                    /opt/local
                    /opt/csw
                    /opt
                    )
            # On 32bit build find the 32bit libs
        ELSE(CMAKE_SIZEOF_VOID_P EQUAL 8)
            FIND_LIBRARY(box2dMAIN_LIBRARY
                    NAMES box2dmain
                    HINTS
                    ${box2d}
                    $ENV{box2d}
                    PATH_SUFFIXES lib
                    lib/x86
                    i686-w64-mingw32/lib
                    PATHS
                    /sw
                    /opt/local
                    /opt/csw
                    /opt
                    )
        ENDIF(CMAKE_SIZEOF_VOID_P EQUAL 8)
    ENDIF(NOT ${box2d_INCLUDE_DIR} MATCHES ".framework")
ENDIF(NOT box2d_BUILDING_LIBRARY)

# box2d may require threads on your system.
# The Apple build may not need an explicit flag because one of the
# frameworks may already provide it.
# But for non-OSX systems, I will use the CMake Threads package.
IF(NOT APPLE)
    FIND_PACKAGE(Threads)
ENDIF(NOT APPLE)

# MinGW needs an additional library, mwindows
# It's total link flags should look like -lmingw32 -lbox2dmain -lbox2d -lmwindows
# (Actually on second look, I think it only needs one of the m* libraries.)
IF(MINGW)
    SET(MINGW32_LIBRARY mingw32 CACHE STRING "mwindows for MinGW")
ENDIF(MINGW)

SET(box2d_FOUND "NO")
IF(box2d_LIBRARY_TEMP)
    # For box2dmain
    IF(NOT box2d_BUILDING_LIBRARY)
        IF(box2dMAIN_LIBRARY)
            SET(box2d_LIBRARY_TEMP ${box2dMAIN_LIBRARY} ${box2d_LIBRARY_TEMP})
        ENDIF(box2dMAIN_LIBRARY)
    ENDIF(NOT box2d_BUILDING_LIBRARY)

    
    # For MinGW library
    IF(MINGW)
        SET(box2d_LIBRARY_TEMP ${MINGW32_LIBRARY} ${box2d_LIBRARY_TEMP})
    ENDIF(MINGW)

    # Set the final string here so the GUI reflects the final state.
    SET(box2d_LIBRARY ${box2d_LIBRARY_TEMP} CACHE STRING "Where the box2d Library can be found")
    # Set the temp variable to INTERNAL so it is not seen in the CMake GUI
    SET(box2d_LIBRARY_TEMP "${box2d_LIBRARY_TEMP}" CACHE INTERNAL "")

    SET(box2d_FOUND "YES")
ENDIF(box2d_LIBRARY_TEMP)

INCLUDE(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(box2d REQUIRED_VARS box2d_LIBRARY box2d_INCLUDE_DIR)