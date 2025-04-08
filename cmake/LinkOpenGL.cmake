# OpenGL

macro(LinkOpenGL TARGET ACCESS)
    
    find_package(OpenGL REQUIRED)

    if (OpenGL_FOUND)

        message(STATUS "[OpenGL]: Libararies - ${OPENGL_LIBRARIES}\n")
        target_include_directories(${TARGET} ${ACCESS} ${OPENGL_INCLDUE_DIRS})
        target_link_libraries(${TARGET} ${ACCESS} ${OPENGL_LIBRARIES})

    else()

        message(FATAL_ERROR "OpenGL was not found on the system.\n")

    endif()

endmacro()
