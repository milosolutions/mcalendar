if (POLICY CMP0048)
    cmake_policy(SET CMP0048 NEW)
endif ()

project(mcalendar
  VERSION 0.0.1
  DESCRIPTION "Milo Calendar"
  LANGUAGES CXX
)

find_package(Qt5 COMPONENTS REQUIRED Core Gui Widgets)

set(CMAKE_AUTOMOC ON)

add_compile_definitions(MCALENDAR_LIB)

set(SOURCES
  mcalendar.h
  mcalendar.cpp
  sampleday.h
  sampleday.cpp
)

set(OTHER_FILES README.md mcalendar.doxyfile)

add_library(mcalendar STATIC ${SOURCES} ${OTHER_FILES})

target_include_directories(mcalendar
  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

target_link_libraries(mcalendar
  Qt5::Core
  Qt5::Gui
  Qt5::Widgets
)

add_subdirectory(test_mcalendar)
