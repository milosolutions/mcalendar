
project(mcalendar
  VERSION 0.0.1
  DESCRIPTION "Milo Log"
  LANGUAGES CXX
)

find_package(Qt5 COMPONENTS REQUIRED Core Gui Widgets)

add_compile_definitions(MCALENDAR_LIB)

set(SOURCES mcalendar.h mcalendar.cpp sampleday.h sampleday.cpp)

set(OTHER_FILES README.md AUTHORS.md mlog.doxyfile)

add_library(mcalendar OBJECT ${SOURCES} ${OTHER_FILES})

target_include_directories(mcalendar
  PUBLIC
  $<INSTALL_INTERFACE:include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

target_link_libraries(mcalendar
  Qt5::Core
  Qt5::Gui
  Qt5::Widgets
)

message("MCalendar: missing unit test!")
#add_subdirectory(tst_mcalendar)
