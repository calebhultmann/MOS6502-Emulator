include(AddGoogleTest)

add_executable(
  unit_tests
  cpu_testing.cpp
)
target_link_libraries(
  unit_tests PRIVATE calculator GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(unit_tests)