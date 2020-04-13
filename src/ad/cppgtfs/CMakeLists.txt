file(GLOB_RECURSE cppgtfs_SOURCES *.cpp)

include_directories(
	${CPPGTFS_INCLUDE_DIR}
)

add_library(cppgtfs
		Writer.cpp
		gtfs/Service.cpp)

target_include_directories(cppgtfs PUBLIC ${CPPGTFS_INCLUDE_DIR})
target_link_libraries(cppgtfs csvparser project_options project_warnings)
