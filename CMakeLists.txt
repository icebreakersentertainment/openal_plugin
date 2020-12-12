cmake_minimum_required(VERSION 3.1.0)

project(openalsoft_plugin)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(OPENALSOFT_PLUGIN_COMPILER_FLAGS "")
set(OPENALSOFT_PLUGIN_DEFINITIONS "")
if(MSVC)
  list(APPEND OPENALSOFT_PLUGIN_COMPILER_FLAGS /EHsc /MP)
  if(CMAKE_BUILD_TYPE MATCHES DEBUG)
    list(APPEND OPENALSOFT_PLUGIN_COMPILER_FLAGS /EHsc /MP)
  endif()
endif()

add_subdirectory(./openalsoft/openal-soft)

if(NOT TARGET SDL2)
  add_subdirectory(./sdl/SDL)
endif()

if(CMAKE_BUILD_TYPE MATCHES Debug OR CMAKE_BUILD_TYPE MATCHES RelWithDebInfo OR ICEENGINE_ENABLE_DEBUG_LOGGING)
  list(APPEND OPENALSOFT_PLUGIN_DEFINITIONS -DICEENGINE_ENABLE_DEBUG_LOGGING)
endif()

if(ICEENGINE_ENABLE_TRACE_LOGGING)
  list(APPEND OPENALSOFT_PLUGIN_DEFINITIONS -DICEENGINE_ENABLE_TRACE_LOGGING)
endif()

# Headers
include_directories(include)

# Source
file(GLOB_RECURSE SOURCES "src/*.cpp")

add_library(openalsoft_plugin SHARED ${SOURCES})

target_include_directories(openalsoft_plugin PRIVATE ${ICEENGINE_INCLUDE_DIRS})
target_include_directories(openalsoft_plugin PRIVATE ${BOOST_INCLUDE_DIRS})
target_include_directories(openalsoft_plugin PRIVATE ${GLM_INCLUDE_DIRS})
target_include_directories(openalsoft_plugin PRIVATE openalsoft/openal-soft/include)
target_include_directories(openalsoft_plugin PRIVATE sdl/SDL/include)

target_compile_definitions(openalsoft_plugin PRIVATE ${OPENALSOFT_PLUGIN_DEFINITIONS})
target_compile_options(openalsoft_plugin PRIVATE ${OPENALSOFT_PLUGIN_COMPILER_FLAGS})

target_link_libraries(openalsoft_plugin OpenAL)
target_link_libraries(openalsoft_plugin SDL2)