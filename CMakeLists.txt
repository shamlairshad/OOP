cmake_minimum_required(VERSION 3.16)
project(member2_attendance LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(member2
    src/AttendanceCorrection.cpp
    src/AttendanceRecord.cpp
    src/AttendanceRegister.cpp
    src/AttendanceReport.cpp
    src/AttendanceSession.cpp
    src/AttendanceStatus.cpp
    src/SessionCode.cpp
    src/SessionCodeCapture.cpp
    src/Timetable.cpp
    src/TimeSlot.cpp)
target_include_directories(member2 PUBLIC include)

add_executable(member2_smoke_test tests/member2_smoke_test.cpp)
target_link_libraries(member2_smoke_test PRIVATE member2)

enable_testing()
add_test(NAME member2_smoke_test COMMAND member2_smoke_test)
