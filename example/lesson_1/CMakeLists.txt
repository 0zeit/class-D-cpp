cmake_minimum_required(VERSION 3.28)

add_executable(lesson1 main.cpp)

target_link_libraries(lesson1 PRIVATE ClassDCPP)

add_custom_command(
    TARGET lesson1 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:lesson1>/res
    COMMENT "Copying resource files to output directory")