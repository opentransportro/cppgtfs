file(GLOB_RECURSE cppgtfs_SOURCES *.cpp)

include_directories(
	${CPPGTFS_INCLUDE_DIR}
)

add_library(cppgtfs ${cppgtfs_SOURCES})
target_link_libraries(cppgtfs csvparser)
