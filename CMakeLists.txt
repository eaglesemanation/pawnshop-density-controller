cmake_minimum_required(VERSION 3.16)

project(
	Pawnshop
	VERSION 0.1.0
	DESCRIPTION "Controlls rails and scales in automated pawnshop"
	LANGUAGES CXX)

# True if this project is main and not included with add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    # Script for running conan inside cmake
    if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
        message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
        file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/v0.16.1/conan.cmake"
            "${CMAKE_BINARY_DIR}/conan.cmake"
            EXPECTED_HASH SHA256=396e16d0f5eabdc6a14afddbcfff62a54a7ee75c6da23f32f7a31bc85db23484
            TLS_VERIFY ON)
    endif()
    include(${CMAKE_BINARY_DIR}/conan.cmake)
    conan_cmake_autodetect(settings)
    conan_cmake_install(PATH_OR_REFERENCE ${CMAKE_SOURCE_DIR}
        BUILD missing
        REMOTE conancenter
        SETTINGS ${settings})

    if(EXISTS "${CMAKE_BINARY_DIR}/conan_paths.cmake")
        message(STATUS "Using conan for dependencies")
        include(${CMAKE_BINARY_DIR}/conan_paths.cmake)
    endif()

	# Provides IDE's with information about folders
	set_property(GLOBAL PROPERTY USE_FOLDERS ON)
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

	find_package(Doxygen)
	if(Doxygen_FOUND)
		add_subdirectory(docs)
	else()
		message(STATUS "Doxygen not found, docs build skipped")
	endif()

    find_package(doctest)
endif()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

find_package(Threads REQUIRED)
find_package(Gpiod REQUIRED)
find_package(PahoMqttCpp REQUIRED)
find_package(SQLite3 REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(fmt REQUIRED)
find_package(spdlog REQUIRED)
find_package(readerwriterqueue REQUIRED)
find_package(tomlplusplus REQUIRED)

include(CTest)
include(doctest)

add_subdirectory(src)
add_subdirectory(apps)
