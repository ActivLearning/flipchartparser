# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

#import zlib
add_subdirectory(./3rdparty/zlib)
#find_package(zlib REQUIRED)

if (${ANDROID_ABI} STREQUAL "armeabi-v7a")
    message("armeabi-v7a")
endif()

if (${ANDROID_ABI} STREQUAL "arm64-v8a")
    message("arm64-v8a")
endif()

if (${ANDROID_ABI} STREQUAL "x86")
    message("x86")
endif()

if (${ANDROID_ABI} STREQUAL "x86_64")
    message("x86_64")
endif()


# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.
aux_source_directory(src DIR_SRCS)
aux_source_directory(src/io IO_LIST)
aux_source_directory(src/objects OBJECTS_LIST)
aux_source_directory(src/resources RESOURCES_LIST)
aux_source_directory(src/global GLOBAL_LIST)
aux_source_directory(src/dataStruct DataStruct_LIST)
aux_source_directory(src/util Util_LIST)
aux_source_directory(src/serialization Serialization_LIST)
message("--------" ${DIR_SRCS} )

add_library( # Sets the name of the library.
        native-lib

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        native-lib.cpp
        ${DIR_SRCS}
        ${IO_LIST}
        ${OBJECTS_LIST}
        ${RESOURCES_LIST}
        ${GLOBAL_LIST}
        ${DataStruct_LIST}
        ${Util_LIST}
        ${Serialization_LIST}
        )



add_library(
        Qt5Core
        SHARED
        IMPORTED
)

#message("---->" "${CMAKE_SOURCE_DIR}/../lib/${ANDROID_ABI}/libQt5Core.so")

set_target_properties(
        Qt5Core
        PROPERTIES IMPORTED_LOCATION
        "${CMAKE_SOURCE_DIR}/../lib/${ANDROID_ABI}/libQt5Core_${ANDROID_ABI}.so"
)


set( QT5INCLUDE
        "${CMAKE_SOURCE_DIR}/include"
        "${CMAKE_SOURCE_DIR}/include/QtCore"
)

IF (WIN32)
	MESSAGE(STATUS "Now is windows")
        set (JAVA_INC "$ENV{JAVA_HOME}/include" 
              "$ENV{JAVA_HOME}/include/win32"
)
ELSEIF (APPLE)
	MESSAGE(STATUS "Now is Apple systens.")
        set (JAVA_INC "$ENV{JAVA_HOME}/include" 
              "$ENV{JAVA_HOME}/include/darwin"
)
ELSEIF (UNIX)
	MESSAGE(STATUS "Now is UNIX-like OS's.")
ENDIF ()



target_include_directories(
        native-lib
        PRIVATE
        ${QT5INCLUDE}
        ${JAVA_INC}
        ${CMAKE_SOURCE_DIR}/src/serialization
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

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
        native-lib

        # Links the target library to the log library
        # included in the NDK.
        ${log-lib}
        Qt5Core
        zlib
        )
