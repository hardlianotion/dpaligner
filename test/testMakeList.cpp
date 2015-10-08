#define CATCH_CONFIG_MAIN 
#include <catch.hpp>
#include <smithwaterman.h>

using namespace std;

TEST_CASE("Just checking that globbing works for CMake") {
    INFO("If we see this, the test file was automatially added to build.")
    CHECK(dummyFunction());
}

