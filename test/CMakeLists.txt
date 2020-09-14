add_executable(sonar-test test.cpp)
target_link_libraries(sonar-test gtest_main)
add_test(sonar-test sonar-test)
