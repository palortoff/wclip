Project(wclip)

set(wclip_version_major 0)
set(wclip_version_minor 2)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_FLAGS_RELEASE "/MT")
set(CMAKE_CXX_FLAGS_DEBUG "/MTd")

get_filename_component(DIST_PATH ./dist REALPATH)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${DIST_PATH}/Debug")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${DIST_PATH}/Release")

add_subdirectory(src)
