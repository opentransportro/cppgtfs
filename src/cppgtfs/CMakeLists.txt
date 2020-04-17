file(GLOB_RECURSE cppgtfs_SOURCES *.cpp)

include_directories(
	${CPPGTFS_INCLUDE_DIR}
)

add_library(cppgtfs
        Writer.cpp
        Reader.cpp
        DataExtractor.cpp
		util/Time.cpp
		exceptions/ParseException.cpp
		exceptions/FileNotFoundException.cpp
		gtfs/Service.cpp
		gtfs/Agency.cpp
        gtfs/Fare.cpp
		gtfs/Stop.cpp
		gtfs/Shape.cpp
		gtfs/StopTime.cpp
		gtfs/Transfer.cpp
		gtfs/Feed.cpp
		gtfs/Frequency.cpp)

target_include_directories(cppgtfs PUBLIC ${CPPGTFS_INCLUDE_DIR})
target_link_libraries(cppgtfs csvparser project_options project_warnings)
