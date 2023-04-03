add_executable(fuaekt
               core/core.c
               core/error.c
               filesystem/filesystem.c
               material/material.c
               renderer/window.c
               main.c
              )

target_link_libraries(fuaekt glfw ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})