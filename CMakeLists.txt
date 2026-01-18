# The following lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.5)

execute_process(
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/version_generator.sh # Path to your script
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}      # Set working directory
    RESULT_VARIABLE SCRIPT_RESULT                      # Store the result code
    OUTPUT_VARIABLE SCRIPT_OUTPUT                      # Store the script's stdout
    ERROR_VARIABLE SCRIPT_ERROR                        # Store the script's stderr
)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
get_filename_component(ProjectId ${CMAKE_CURRENT_LIST_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId})

# Include espfs ROM in foldef HTML
include(components/webguiapp/extlibs/libespfs/cmake/include.cmake)
target_add_espfs(WebguiappTemplate.elf espfs webui/dist/spa)