cmake_minimum_required(VERSION 3.28)

set(PJNAME "problem1")

add_executable(${PJNAME} 1_1.cpp) # 여기에 적힌 파일명을 수정하여 연습문제 빌드

target_link_libraries(${PJNAME} PRIVATE ClassDCPP)

add_custom_command(
    TARGET ${PJNAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PJNAME}>/res
    COMMENT "Copying resource files to output directory")