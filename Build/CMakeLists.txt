## Leaf OpenGL
cmake_minimum_required (VERSION 2.8)

project(LOpenGL)

aux_source_directory(../LOpenGL/src DIRSRCS)

aux_source_directory(../GLAD/src DIR_GLAD_SRCS)
aux_source_directory(../GLAD/include/KHR DIR_KHR_INCS)
aux_source_directory(../GLAD/include/glad DIR_GLAD_INCS)

#add_subdirectory(GLAD)
#add_subdirectory(LOpenGL)

include_directories(../GLAD/include)

add_executable(LMain ${DIRSRCS} ${DIR_GLAD_SRCS} ${DIR_KHR_INCS} ${DIR_GLAD_INCS})
