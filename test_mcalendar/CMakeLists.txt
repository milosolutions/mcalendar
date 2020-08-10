find_package(Qt5 COMPONENTS Core Gui Widgets Test REQUIRED)

set(CMAKE_AUTOMOC ON)

add_executable(test_mcalendar tst_mcalendartest.cpp)

target_link_libraries(test_mcalendar mcalendar
  Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Test
)

add_test(test_mcalendar test_mcalendar)
