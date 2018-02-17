project(ut)
cmake_minimum_required(VERSION 2.8)

# Locate GTest
find_package(GTest REQUIRED GTEST_ROOT=/home/mitikkak/googletest/googletest)
set(EXTERNALS_DIR ${PROJECT_ROOT}/externals)
MESSAGE("Externals: ${EXTERNALS_DIR}")
set(ACCELEROMETER_DIR ${EXTERNALS_DIR}/ADXL345)
MESSAGE("Accelerometer: ${ACCELEROMETER_DIR}")
set(KAYAK_LOGGER_SRC_DIR ${PROJECT_ROOT})
set(STUBS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/stubs)
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(${KAYAK_LOGGER_SRC_DIR})
include_directories(${ACCELEROMETER_DIR})
include_directories(${STUBS_DIR})

add_definitions(-DUNIT_TEST)

set( CMAKE_BUILD_TYPE Debug)
aux_source_directory(. TEST_SRC)
aux_source_directory(${ACCELEROMETER_DIR} ACCELEROMETER_SRC)
aux_source_directory(${STUBS_DIR} STUBS_SRC)
aux_source_directory(${KAYAK_LOGGER_SRC_DIR} KAYAK_LOGGER_SRC)
add_executable(${PROJECT_NAME} ${TEST_SRC} ${ACCELEROMETER_SRC} ${STUBS_SRC} ${KAYAK_LOGGER_SRC})
target_link_libraries(${PROJECT_NAME} ${GTEST_LIBRARIES} pthread)