project(napd LANGUAGES CXX)

cmake_minimum_required(VERSION 3.6 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 5.7 COMPONENTS Core DBus)

### Main library ###
add_library(nap
    src/lib/collection/CheckedProcesses.cpp
    src/lib/collection/CustomChecks.cpp
    src/lib/collection/CheckedUnits.cpp
    src/lib/collection/CheckedPIDs.cpp
    src/lib/PowerManager.cpp
    src/lib/ProcessHandler.cpp
    src/lib/NapDaemon.cpp
    src/lib/Settings.cpp
    src/lib/DBusManager.cpp

    src/lib/collection/CustomChecks.h
    src/lib/collection/CheckedPIDs.h
    src/lib/collection/CheckedUnits.h
    src/lib/collection/Collection.h
    src/lib/collection/CheckedProcesses.h
    src/lib/checkable/Checkable.h
    src/lib/checkable/Process.h
    src/lib/checkable/CustomCheck.h
    src/lib/checkable/PID.h
    src/lib/checkable/Unit.h
    src/lib/PowerManager.h
    src/lib/ProcessHandler.h
    src/lib/NotReadyException.h
    src/lib/NapDaemon.h
    src/lib/Settings.h
    src/lib/DBusManager.h
    )
    
target_link_libraries(nap PUBLIC Qt5::DBus)
target_include_directories(nap PUBLIC src/lib)

### napd ###
add_executable(napd src/app/main.cpp)
target_link_libraries(napd nap)

### napctl ###
add_executable(napctl
    src/napctl/main.cpp
    src/napctl/NapCtl.cpp
    src/napctl/MessageListener.cpp
    
    src/napctl/NapCtl.h
    src/napctl/MessageListener.h)
    
target_link_libraries(napctl Qt5::DBus)

install(TARGETS napd napctl
        RUNTIME DESTINATION bin)
