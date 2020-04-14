file(GLOB_RECURSE cppgtfs_SOURCES *.cpp)

include_directories(
	${CPPGTFS_INCLUDE_DIR}
)

add_library(cppgtfs
		Writer.cpp
		gtfs/Service.cpp
		gtfs/flat/Time.cpp
		gtfs/flat/Agency.cpp
		gtfs/flat/Fare.cpp
		gtfs/flat/Frequency.cpp
		gtfs/flat/Route.cpp
		gtfs/flat/Service.cpp
		gtfs/flat/Shape.cpp
		gtfs/flat/Stop.cpp
		gtfs/flat/StopTime.cpp
		gtfs/flat/Transfer.cpp
		gtfs/flat/Trip.cpp)

target_include_directories(cppgtfs PUBLIC ${CPPGTFS_INCLUDE_DIR})
target_link_libraries(cppgtfs csvparser project_options project_warnings)
