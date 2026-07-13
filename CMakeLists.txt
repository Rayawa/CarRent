cmake_minimum_required(VERSION 3.10)
project(CarRent VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCES
    src/main.cpp
    src/vehicle.cpp
    src/renter.cpp
    src/rent_record.cpp
    src/utils.cpp
    src/auth.cpp
    src/logger.cpp
    src/vehicle_manager.cpp
    src/renter_manager.cpp
    src/rent_manager.cpp
    src/receipt.cpp
    src/statistics.cpp
    src/ui.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)
endif()
