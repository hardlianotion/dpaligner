include_directories(${PROJECT_SOURCE_DIR}/source)

file(GLOB_RECURSE sourceList . *.cpp)
add_executable(testRun ${sourceList})

set_property(TARGET testRun PROPERTY CXX_STANDARD 11)
set_property(TARGET testRun PROPERTY CXX_STANDARD_REQUIRED ON)

link_directories(CMAKE_BINARY_DIR/source)
target_link_libraries(testRun dpaligner)

