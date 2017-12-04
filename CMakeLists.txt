cmake_minimum_required(VERSION 3.1)
project(halide-cmake-test)

# scan src/
file(GLOB CPP_FILES src/*.cpp)
file(GLOB_RECURSE HPP_FILES src/*.h src/*.hpp)
set(INCLUDE_DIRS src .)

set(HLPIPES_ROOT hl-pipelines)
add_subdirectory(ext/hlpipes)
list(APPEND LIBS hl_pipelines)
list(APPEND INCLUDE_DIRS ${HALIDE_DIR}/include)

# Android JNI libs
if (ANDROID)
    find_library(LLOG NAMES log PATHS $ENV{SYSROOT}/usr/lib)
    list(APPEND LIBS ${LLOG})
endif ()

set(WITH_GL ON)

if (WITH_GL)
	add_definitions(-DWITH_GL)   
	
    if (ANDROID)
        list(APPEND LIBS -lEGL -lGLESv3)
        list(APPEND EXTRA_SOURCES)
    else ()
        find_package(OpenGL)
        find_package(GLUT)
        list(APPEND LIBS ${OPENGL_LIBRARIES})
    endif ()
	
	file(GLOB OPENGL_FILES src/opengl/*.cpp)
	list(APPEND EXTRA_SOURCES ${OPENGL_FILES})	
endif ()

if (NOT WIN32 AND NOT ANDROID)
    #find_package(GLUT REQUIRED)  # linux X stuff for opengl
    list(APPEND LIBS -ldl -lpthread -lz -g)
endif ()

include_directories(${INCLUDE_DIRS})

add_executable(halide-cmake-test ${CPP_FILES} ${HPP_FILES} ${EXTRA_SOURCES})
target_link_libraries(halide-cmake-test ${LIBS})
