
file(GLOB_RECURSE lib_sources . *.cpp) 

add_library(dpaligner STATIC ${lib_sources})
set_property(TARGET dpaligner PROPERTY CXX_STANDARD 11)
set_property(TARGET dpaligner PROPERTY CXX_STANDARD_REQUIRED ON)
