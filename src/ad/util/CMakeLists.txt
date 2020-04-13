add_library(csvparser CsvParser.cpp CsvWriter.cpp)

target_include_directories(csvparser PUBLIC ${CPPGTFS_INCLUDE_DIR})
target_link_libraries(csvparser project_options project_warnings)
