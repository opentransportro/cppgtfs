file(GLOB_RECURSE util_SOURCES *.cpp)

add_library(csvparser ${util_SOURCES})
