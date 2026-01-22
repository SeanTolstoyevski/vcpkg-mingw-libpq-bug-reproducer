cmake_minimum_required(VERSION 3.15)
project(poco_postgresql_example)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")


if(DEFINED ENV{VCPKG_ROOT})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "Vcpkg toolchain file")
endif()

find_package(Poco REQUIRED COMPONENTS Data DataPostgreSQL Foundation)

find_package(PostgreSQL REQUIRED)

add_executable(poco_postgres_example main.cpp)

target_link_libraries(poco_postgres_example
    PRIVATE
    Poco::Data
    Poco::DataPostgreSQL
    Poco::Foundation
    PostgreSQL::PostgreSQL
)

target_include_directories(poco_postgres_example
    PRIVATE
    ${PostgreSQL_INCLUDE_DIRS}
)
