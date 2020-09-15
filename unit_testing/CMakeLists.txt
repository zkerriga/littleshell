project(Google_tests)

#add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(TEST_FILES
        parse_test.cpp
        )

add_executable(Google_Tests_run ${TEST_FILES})
target_link_libraries(Google_Tests_run gtest gtest_main)
target_link_libraries(Google_Tests_run test)
#target_link_libraries(Google_Tests_run ${LBSD_DIR})