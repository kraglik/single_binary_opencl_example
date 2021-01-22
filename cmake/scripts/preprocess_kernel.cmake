set(template "${CMAKE_CURRENT_LIST_DIR}/preprocessed_kernel.template")

file(READ ${SRC} CL_SOURCE_CODE)

string(REGEX REPLACE "\\\\" "\\\\\\\\" CL_SOURCE_CODE "${CL_SOURCE_CODE}")
string(REGEX REPLACE "\"" "\\\\\"" CL_SOURCE_CODE "${CL_SOURCE_CODE}")

string(REGEX REPLACE "\r?\n$" "" CL_SOURCE_CODE "${CL_SOURCE_CODE}")
string(REGEX REPLACE "\r?\n" "\\\\n\"\n\"" CL_SOURCE_CODE "\"${CL_SOURCE_CODE}\\n\"")

file(WRITE ${DST} "${CL_SOURCE_CODE}")

configure_file(${template} ${DST} @ONLY)