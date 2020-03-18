cmake_minimum_required(VERSION 3.5)

set(CMAKE_AUTOMOC ON)

find_package(Qt5 COMPONENTS Core Gui Widgets Test REQUIRED)

set(TEST_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/tst_mcalendartest.cpp
)

set(APP_SRC
    ${PROJECT_SOURCE_DIR}/mcalendar.h
    ${PROJECT_SOURCE_DIR}/mcalendar.cpp
    ${PROJECT_SOURCE_DIR}/daterange.h
    ${PROJECT_SOURCE_DIR}/timerange.h
)

add_executable(mcalendar_test ${TEST_SRC} ${APP_SRC})

target_include_directories(mcalendar_test PRIVATE ${PROJECT_SOURCE_DIR})

qt5_use_modules(mcalendar_test Core Gui Widgets Test)
