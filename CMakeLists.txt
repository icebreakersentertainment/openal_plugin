cmake_minimum_required(VERSION 3.1.0)

project(openalsoft_plugin)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(OPENALSOFT_PLUGIN_COMPILER_FLAGS "")
if(MSVC)
  set(OPENALSOFT_PLUGIN_COMPILER_FLAGS "/EHsc /MP")
  if(CMAKE_BUILD_TYPE MATCHES DEBUG)
    set(OPENALSOFT_PLUGIN_COMPILER_FLAGS "/EHsc /MP")
  endif()
endif()

add_subdirectory(./openalsoft/openal-soft)

# Headers
include_directories(include)

# Source
file(GLOB_RECURSE SOURCES "src/*.cpp")

add_library(openalsoft_plugin SHARED ${SOURCES})

target_include_directories(openalsoft_plugin PRIVATE ${ICEENGINE_INCLUDE_DIRS})
target_include_directories(openalsoft_plugin PRIVATE ${BOOST_INCLUDE_DIRS})
target_include_directories(openalsoft_plugin PRIVATE ${GLM_INCLUDE_DIRS})
target_include_directories(openalsoft_plugin PRIVATE openalsoft/openal-soft/include)

target_compile_options(openalsoft_plugin PRIVATE ${OPENALSOFT_PLUGIN_COMPILER_FLAGS})

target_link_libraries(openalsoft_plugin OpenAL)