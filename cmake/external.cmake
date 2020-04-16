include(ExternalProject)

set(EXTERNAL_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/3rdparty)
set(EXTERNAL_DOWNLOAD_LOCATION ${CMAKE_BINARY_DIR}/3rdparty/sources)

find_package(Git QUIET)
if(GIT_FOUND)
    ExternalProject_Add(catch2
            GIT_REPOSITORY https://github.com/catchorg/Catch2
            PREFIX ${EXTERNAL_DOWNLOAD_LOCATION}
            CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION} -DCATCH_BUILD_EXAMPLES=OFF
            LOG_DOWNLOAD ON)

    include(${EXTERNAL_INSTALL_LOCATION}/lib/cmake/Catch2/Catch.cmake OPTIONAL)

    ExternalProject_Add(nameof
            GIT_REPOSITORY https://github.com/Neargye/nameof
            GIT_TAG v0.9.3
            PREFIX ${EXTERNAL_DOWNLOAD_LOCATION}
            CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION})

    ExternalProject_Add(googletest
            GIT_REPOSITORY https://github.com/google/googletest
            PREFIX ${EXTERNAL_DOWNLOAD_LOCATION}
            CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION})

else()
    message(FATAL_ERROR "You need git to get things working")
endif()


include_directories(${EXTERNAL_INSTALL_LOCATION}/include)
link_directories(${EXTERNAL_INSTALL_LOCATION}/lib)

#set(CMAKE_MODULE_PATH "${EXTERNAL_INSTALL_LOCATION}/lib/cmake/;${CMAKE_MODULE_PATH}")

#message("${CMAKE_MODULE_PATH}")
