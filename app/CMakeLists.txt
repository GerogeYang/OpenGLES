# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# Set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/jniLibs/${Android_ABI})

include_directories(src/main/cpp/include)
include_directories(src/main/cpp/include/element)
include_directories(src/main/cpp/include/matrix)
include_directories(src/main/cpp/include/md2)
include_directories(src/main/cpp/include/model)
include_directories(src/main/cpp/include/shape)
include_directories(src/main/cpp/include/util)

aux_source_directory(src/main/cpp/element ELEMENT)
aux_source_directory(src/main/cpp/matrix MATRIX)
aux_source_directory(src/main/cpp/modules MODULES)
aux_source_directory(src/main/cpp/modules/md2 MODULES_MD2)
aux_source_directory(src/main/cpp/modules/model MODULES_MODEL)
aux_source_directory(src/main/cpp/modules/shape MODULES_SHAPE)
aux_source_directory(src/main/cpp/util UTIL)

include_directories(src/main/cpp/soil/include)
aux_source_directory(src/main/cpp/soil SOIL)

include_directories(src/main/cpp/assimp/include)
include_directories(src/main/cpp/assimp/contrib/irrXML)
include_directories(src/main/cpp/assimp/contrib/openddlparser/include)
include_directories(src/main/cpp/assimp/contrib/poly2tri)
include_directories(src/main/cpp/assimp/contrib/unzip)
include_directories(src/main/cpp/assimp/contrib/zip)

aux_source_directory(src/main/cpp/assimp/code ASSIMP)
aux_source_directory(src/main/cpp/assimp/contrib/clipper CLIPPER)
aux_source_directory(src/main/cpp/assimp/contrib/irrXML IRRXML)
aux_source_directory(src/main/cpp/assimp/contrib/openddlparser/code OPENDDLPARSER)
aux_source_directory(src/main/cpp/assimp/contrib/poly2tri POLY2TRI)
aux_source_directory(src/main/cpp/assimp/contrib/unzip UNZIP)
aux_source_directory(src/main/cpp/assimp/contrib/zip ZIP)

add_library(# Sets the name of the library.
            assimp-lib

            # Sets the library as a shared library.
            SHARED

            # Provides a relative path to your source file(s).
            ${CLIPPER}
            ${IRRXML}
            ${OPENDDLPARSER}
            ${POLY2TRI}
            ${UNZIP}
            ${ZIP}
            ${ASSIMP}
           )


# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
             native-lib

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             src/main/cpp/native-lib.cpp
             src/main/cpp/Render.cpp

             ${ELEMENT}
             ${MATRIX}
             ${MODULES}
             ${MODULES_MD2}
             ${MODULES_MODEL}
             ${MODULES_SHAPE}
             ${SOIL}
             ${UTIL}
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
              log )

find_library( # Sets the name of the path variable.
              EGL-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              EGL )

find_library( # Sets the name of the path variable.
              GLESv1-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              GLESv1_CM )

find_library( # Sets the name of the path variable.
              GLESv2-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              GLESv2 )

find_library( # Sets the name of the path variable.
              Android-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              android )

find_library(# Sets the name of the path variable.
              z-lib
              # Specifies the name of the NDK library that
              # you want CMake to locate.
              z
             )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
                       native-lib

                       # Links the target library to the log library
                       # included in the NDK.
                       assimp-lib
                       ${log-lib}
                       ${EGL-lib}
                       ${GLESv1-lib}
                       ${GLESv2-lib}
                       ${Android-lib}
                       )

target_link_libraries( # Specifies the target library.
                       assimp-lib

                       # Links the target library to the log library
                       # included in the NDK.
                       ${z-lib}
                       ${log-lib}
                       ${Android-lib}
                       )


add_dependencies(
                  native-lib
                  assimp-lib
                )