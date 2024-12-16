cmake_minimum_required(VERSION 3.0.0)
project(gnosis VERSION 0.1.0 LANGUAGES C CXX)

# gnosis options
option(GNOSIS_BUILD_TESTS "Enables builds of tests" ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS on)
set(CMAKE_CXX_STANDARD 20)

# unit tests
if(GNOSIS_BUILD_TESTS)
    include(CTest)
    add_subdirectory(test)
endif(GNOSIS_BUILD_TESTS)

# target_include_directories(test_gnosis PRIVATE
#     ${CMAKE_SOURCE_DIR}/include
#     ${CMAKE_SOURCE_DIR}/external
# )



#set(CPACK_PROJECT_NAME ${PROJECT_NAME})
#set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
#include(CPack)
