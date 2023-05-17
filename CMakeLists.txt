cmake_minimum_required(VERSION 3.10)

project(SMA-C++-Project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find cURL package and link it
find_package(CURL REQUIRED)

if(CURL_FOUND)
    message(STATUS "Found CURL: ${CURL_INCLUDE_DIRS}")
    include_directories(${CURL_INCLUDE_DIRS})
else()
    message(FATAL_ERROR "CURL Not Found")
endif()

add_executable(${PROJECT_NAME} main.cpp StockData.cpp SMA.cpp)

# Link the cURL library to your target executable
target_link_libraries(${PROJECT_NAME} PRIVATE ${CURL_LIBRARIES})
