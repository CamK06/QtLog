cmake_minimum_required(VERSION 3.5)
project(qtlog)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(CMAKE_INSTALL_PREFIX "/usr/local")
else()
    set(CMAKE_INSTALL_PREFIX "/usr")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

file(GLOB SOURCES "src/*.cpp")

add_subdirectory(thirdparty/spdlog)

find_package(QT NAMES Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)

if(EXISTS "${CMAKE_SOURCE_DIR}/.git")
  execute_process(
    COMMAND git log -1 --format=%h
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_COMMIT
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )
else()
  set(GIT_COMMIT "unknown")
endif()
add_definitions("-DGIT_COMMIT=\"${GIT_COMMIT}\"")

add_executable(qtlog ${SOURCES})
if (${CMAKE_SYSTEM_NAME} MATCHES "Linux" OR ${CMAKE_SYSTEM_NAME} MATCHES "Haiku")
target_link_libraries(qtlog Qt5::Widgets spdlog fmt stdc++fs)
else()
target_link_libraries(qtlog Qt5::Widgets spdlog fmt)
endif()

install(TARGETS qtlog DESTINATION bin)