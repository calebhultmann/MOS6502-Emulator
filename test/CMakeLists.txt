include(AddGoogleTest)

add_executable(
  arithmetic_tests
  arithmetic_ops.cpp
)
target_link_libraries(
  arithmetic_tests PRIVATE emulator GTest::gtest_main
)

add_executable(
  branch_tests
  branch_ops.cpp
)
target_link_libraries(
  branch_tests PRIVATE emulator GTest::gtest_main
)

add_executable(
  inc_dec_tests
  inc_dec_ops.cpp
)
target_link_libraries(
  inc_dec_tests PRIVATE emulator GTest::gtest_main
)

add_executable(
  jump_tests
  jump_ops.cpp
)
target_link_libraries(
  jump_tests PRIVATE emulator GTest::gtest_main
)

add_executable(
  load_store_tests
  load_store_ops.cpp
)
target_link_libraries(
  load_store_tests PRIVATE emulator GTest::gtest_main
)

add_executable(
  logical_tests
  logical_ops.cpp
)
target_link_libraries(
  logical_tests PRIVATE emulator GTest::gtest_main
)

add_executable(
  register_transfer_tests
  register_transfer_ops.cpp
)
target_link_libraries(
  register_transfer_tests PRIVATE emulator GTest::gtest_main
)

add_executable(
  shift_tests
  shift_ops.cpp
)
target_link_libraries(
  shift_tests PRIVATE emulator GTest::gtest_main
)

add_executable(
  stack_tests
  stack_ops.cpp
)
target_link_libraries(
  stack_tests PRIVATE emulator GTest::gtest_main
)

add_executable(
  status_change_tests
  status_change_ops.cpp
)
target_link_libraries(
  status_change_tests PRIVATE emulator GTest::gtest_main
)

add_executable(
  system_tests
  system_ops.cpp
)
target_link_libraries(
  system_tests PRIVATE emulator GTest::gtest_main
)

add_executable(
  full_system_tests
  arithmetic_ops.cpp
  branch_ops.cpp
  inc_dec_ops.cpp
  jump_ops.cpp
  load_store_ops.cpp
  logical_ops.cpp
  register_transfer_ops.cpp
  shift_ops.cpp
  stack_ops.cpp
  status_change_ops.cpp
  system_ops.cpp
)
target_link_libraries(
  full_system_tests PRIVATE emulator GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(arithmetic_tests)
gtest_discover_tests(branch_tests)
gtest_discover_tests(inc_dec_tests)
gtest_discover_tests(jump_tests)
gtest_discover_tests(load_store_tests)
gtest_discover_tests(logical_tests)
gtest_discover_tests(register_transfer_tests)
gtest_discover_tests(shift_tests)
gtest_discover_tests(stack_tests)
gtest_discover_tests(status_change_tests)
gtest_discover_tests(system_tests)
gtest_discover_tests(full_system_tests)