set(SOURCES
  la_tests.cpp
  )

add_executable(la_tests ${SOURCES})
target_link_libraries(la_tests gtest_main la)
add_test(NAME la_tests COMMAND la_tests)
