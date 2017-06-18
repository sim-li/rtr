include_directories(${Jet_INCLUDE_DIRS})
link_directories(${Jet_LIBRARY_DIRS})

set(NAME "03-fly-over")

file(GLOB SRCS *.cpp *.h *.vsh *.fsh *.gsh *.vert *.frag *.geom)
add_executable(${NAME} ${SRCS})
target_link_libraries(${NAME} ${Jet_LIBRARIES})
