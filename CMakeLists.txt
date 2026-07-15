cmake_minimum_required(VERSION 3.10)
project(CarRent VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCES
    src/main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
set_source_files_properties(src/main.cpp PROPERTIES OBJECT_DEPENDS "${CMAKE_SOURCE_DIR}/src/car_rent.cpp;${CMAKE_SOURCE_DIR}/src/menu1_vehicle.cpp;${CMAKE_SOURCE_DIR}/src/menu2_renter.cpp;${CMAKE_SOURCE_DIR}/src/menu3_rent.cpp;${CMAKE_SOURCE_DIR}/src/menu4_return.cpp;${CMAKE_SOURCE_DIR}/src/menu5_query.cpp;${CMAKE_SOURCE_DIR}/src/menu6_statistics.cpp;${CMAKE_SOURCE_DIR}/src/menu7_output.cpp;${CMAKE_SOURCE_DIR}/src/menu8_system.cpp;${CMAKE_SOURCE_DIR}/src/menu9_extended.cpp")

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)
endif()
