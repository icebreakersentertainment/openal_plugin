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

if(CMAKE_BUILD_TYPE MATCHES Debug OR CMAKE_BUILD_TYPE MATCHES RelWithDebInfo OR ICEENGINE_ENABLE_DEBUG_LOGGING)
  list(APPEND OPENALSOFT_PLUGIN_DEFINITIONS -DICEENGINE_ENABLE_DEBUG_LOGGING)
endif()

if(ICEENGINE_ENABLE_TRACE_LOGGING)
  list(APPEND OPENALSOFT_PLUGIN_DEFINITIONS -DICEENGINE_ENABLE_TRACE_LOGGING)
endif()

option(ALSOFT_EXAMPLES  "Build example programs"  OFF)
add_subdirectory(./openalsoft/openal-soft)

find_package(glm REQUIRED)
find_package(Boost REQUIRED)
find_package(SDL2 REQUIRED)

# Source
file(GLOB_RECURSE SOURCES "src/*.cpp")

add_library(openalsoft_plugin SHARED ${SOURCES})

# Headers
target_include_directories(openalsoft_plugin PRIVATE include)

target_include_directories(openalsoft_plugin PRIVATE ${ICEENGINE_INCLUDE_DIRS})
target_include_directories(openalsoft_plugin PRIVATE ${Boost_INCLUDE_DIRS})

target_compile_definitions(openalsoft_plugin PRIVATE ${OPENALSOFT_PLUGIN_DEFINITIONS})
target_compile_options(openalsoft_plugin PRIVATE ${OPENALSOFT_PLUGIN_COMPILER_FLAGS})

target_link_libraries(openalsoft_plugin PRIVATE OpenAL)
target_link_libraries(openalsoft_plugin PRIVATE glm::glm)
target_link_libraries(openalsoft_plugin PRIVATE SDL2::SDL2)
