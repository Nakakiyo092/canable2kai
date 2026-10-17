# Generates a header with GIT_VERSION and GIT_REMOTE.
# Run in script mode at every build:
#   cmake -DSOURCE_DIR=<repo> -DOUTPUT=<header> -P git_version.cmake
# The header is rewritten only when its content changes, so an unchanged
# version does not trigger a rebuild.

execute_process(
    COMMAND git describe --abbrev=7 --dirty --always --tags
    WORKING_DIRECTORY ${SOURCE_DIR}
    OUTPUT_VARIABLE GIT_VERSION
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_QUIET
)
execute_process(
    COMMAND git config --get remote.origin.url
    WORKING_DIRECTORY ${SOURCE_DIR}
    OUTPUT_VARIABLE GIT_REMOTE
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_QUIET
)
# Keep the part from "github" on; this drops the scheme and any credentials.
string(REGEX REPLACE "^.*github" "github" GIT_REMOTE "${GIT_REMOTE}")

set(CONTENT "#pragma once\n#define GIT_VERSION \"${GIT_VERSION}\"\n#define GIT_REMOTE \"${GIT_REMOTE}\"\n")

if(EXISTS ${OUTPUT})
    file(READ ${OUTPUT} OLD_CONTENT)
endif()
if(NOT CONTENT STREQUAL OLD_CONTENT)
    file(WRITE ${OUTPUT} "${CONTENT}")
endif()
