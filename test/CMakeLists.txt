############################# GTest fetch ###########################
include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)
FetchContent_MakeAvailable(googletest)

add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)
###################### end of GTest fetch ###########################

add_executable(gameTest gameTest.cpp)

target_link_libraries(gameTest
 PRIVATE
  GTest::GTest
  game)

add_test(games_gTests gameTest)