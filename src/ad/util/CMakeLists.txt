file(GLOB_RECURSE util_SOURCES *.cpp)

add_library(csvparser ${util_SOURCES})
target_link_libraries(csvparser project_options project_warnings)
