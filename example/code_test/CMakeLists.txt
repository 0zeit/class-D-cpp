cmake_minimum_required(VERSION 3.28)

set(PJNAME "code_test")

add_executable(${PJNAME} main.cpp)

target_link_libraries(${PJNAME} PRIVATE ClassDCPP)

add_custom_command(
    TARGET ${PJNAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PJNAME}>/res
    COMMENT "Copying resource files to output directory")