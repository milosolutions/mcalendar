if (POLICY CMP0048)
        cmake_policy(SET CMP0048 NEW)
endif ()

project(mcalendar
  VERSION 0.0.1
  DESCRIPTION "Milo Log"
  LANGUAGES CXX
)

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

add_compile_definitions(MCALENDAR_LIB)

set(SOURCES 
    mcalendar.h
    mcalendar.cpp
    sampleday.h
    sampleday.cpp
)

set(OTHER_FILES README.md mcalendar.doxyfile)

add_library(mcalendar OBJECT ${SOURCES} ${OTHER_FILES})

target_include_directories(mcalendar
  PUBLIC
  $<INSTALL_INTERFACE:include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

qt5_use_modules(mcalendar Core Gui Widgets)

enable_testing()
add_subdirectory(test_mcalendar)
add_test(NAME MCalendarTest COMMAND mcalendar_test)
