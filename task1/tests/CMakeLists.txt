find_package(GTest 1.17.0 REQUIRED)

add_executable(tests
               variance_test.cpp
               gen_selection_test.cpp
)

target_include_directories(tests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/)

target_link_libraries(tests PRIVATE fp GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(tests)
