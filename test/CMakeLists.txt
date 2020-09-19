add_executable(sonar-test
    ParseValue.cpp
    ParseArray.cpp
    )

include_directories(${PROJECT_SOURCE_DIR}/include)
target_link_libraries(sonar-test gtest_main sonar)
add_test(sonar-test sonar-test)
