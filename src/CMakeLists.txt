project(wclip)

configure_file(
  ${PROJECT_SOURCE_DIR}/version.h.in
  ${PROJECT_BINARY_DIR}/version.h
)

set(SOURCES
  main.cpp
  Clipboard.cpp
  Options.cpp
)

set(HEADERS
  Clipboard.h
  Options.h
)

add_executable(${PROJECT_NAME} ${SOURCES})
