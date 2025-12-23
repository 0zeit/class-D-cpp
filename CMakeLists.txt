cmake_minimum_required(VERSION 3.28)
project(ClassDCPP VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(ClassDCPP_BUILD_EXAMPLE "Build example projects" ${PROJECT_IS_TOP_LEVEL})
option(ClassDCPP_BUILD_TEST "Build tests" OFF)
option(ClassDCPP_BUILD_DOCS "Build documentation" OFF)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(ClassDCPP INTERFACE)

include(FetchContent)
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

target_include_directories(ClassDCPP INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include>)
target_compile_features(ClassDCPP INTERFACE cxx_std_20)

FetchContent_Declare(SFML GIT_REPOSITORY https://github.com/SFML/SFML.git GIT_BRANCH master GIT_SHALLOW ON EXCLUDE_FROM_ALL SYSTEM)
FetchContent_MakeAvailable(SFML)

target_link_libraries(ClassDCPP INTERFACE sfml-system sfml-window sfml-graphics sfml-audio sfml-network)

if(MSVC)
    target_compile_options(ClassDCPP INTERFACE /W4)
    target_compile_definitions(ClassDCPP INTERFACE NOMINMAX WIN32_LEAN_AND_MEAN)
else()
    target_compile_options(ClassDCPP INTERFACE -Wall -Wextra -Wpedantic -Werror)
endif()

if(ClassDCPP_BUILD_EXAMPLE)
    add_subdirectory(example)
endif()

if(ClassDCPP_BUILD_TEST)
    add_subdirectory(test)
endif()

install(TARGETS ClassDCPP EXPORT ClassDCPPTargets)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

write_basic_package_version_file("ClassDCPPConfigVersion.cmake" VERSION ${PROJECT_VERSION} COMPATIBILITY SameMajorVersion)
configure_package_config_file("${CMAKE_CURRENT_SOURCE_DIR}/cmake/ClassDCPPConfig.cmake.in" "${CMAKE_CURRENT_BINARY_DIR}/ClassDCPPConfig.cmake" INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ClassDCPP)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/ClassDCPPConfig.cmake" "${CMAKE_CURRENT_BINARY_DIR}/ClassDCPPConfigVersion.cmake" DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ClassDCPP)
install(EXPORT ClassDCPPTargets FILE ClassDCPPTargets.cmake NAMESPACE ClassDCPP:: DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ClassDCPP)