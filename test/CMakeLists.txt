enable_testing()

add_executable(test_gnosis
    test_fix.cpp
    ${PROJECT_SOURCE_DIR}/external/catch2/catch_amalgamated.cpp
)

target_include_directories(test_gnosis PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/external
)

add_test(
    NAME test_gnosis
    COMMAND test_gnosis
)
