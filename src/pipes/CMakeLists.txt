message(STATUS "Processing /src/pipes")

macro(add_pipe arg1)
  set(SRCS_LIST "${SRCS_LIST}" src/pipes/${arg1}.cpp CACHE INTERNAL "SRCS_LIST")
endmacro(add_pipe)

add_pipe(ops)
add_pipe(crop)
add_pipe(threshold)
