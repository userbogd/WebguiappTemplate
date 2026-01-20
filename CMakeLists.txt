# The following lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.5)

option(GENERATE_RELEASE "def OFF" OFF)
if(GENERATE_RELEASE)
execute_process(
    COMMAND quasar b
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/webui    
)

execute_process(
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/version_generator.sh
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}    
)
endif()

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
get_filename_component(ProjectId ${CMAKE_CURRENT_LIST_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId})


# Include espfs ROM in foldef HTML
include(components/webguiapp/extlibs/libespfs/cmake/include.cmake)
target_add_espfs(${PROJECT_NAME}.elf espfs webui/dist/spa)

if(GENERATE_RELEASE)
set(HW_REV 1)
if (CONFIG_BOARD_HARDWARE_REVISION)
    set (HW_REV ${CONFIG_BOARD_HARDWARE_REVISION})
endif()

add_custom_command(TARGET app POST_BUILD
                   COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/output_generator.sh ${PROJECT_NAME} ${HW_REV} ${IDF_TARGET}
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
endif()