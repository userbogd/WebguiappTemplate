# The following lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.5)

execute_process(
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/version_generator.sh
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}    
)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
get_filename_component(ProjectId ${CMAKE_CURRENT_LIST_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId})

# Include espfs ROM in foldef HTML
include(components/webguiapp/extlibs/libespfs/cmake/include.cmake)
target_add_espfs(WebguiappTemplate.elf espfs webui/dist/spa)
message(STATUS "Building project: ${PROJECT_NAME}")
set(HW_REV 1)
if (CONFIG_BOARD_HARDWARE_REVISION)
    set (HW_REV ${CONFIG_BOARD_HARDWARE_REVISION})
endif()

#execute_process(
 #   COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/output_generator.sh ${PROJECT_NAME} ${HW_REV}
  #  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}    
#)

add_custom_command(
	TARGET ${CMAKE_CURRENT_SOURCE_DIR}/build/${PROJECT_NAME}.elf
	POST_BUILD
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/output_generator.sh ${PROJECT_NAME} ${HW_REV}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}  
)



