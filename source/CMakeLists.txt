add_executable(fuaekt
               core/core.c
               core/error.c
               filesystem/filesystem.c
               input/input.c
               material/material.c
               renderer/renderer.c
               renderer/window.c
               main.c
              )

target_link_libraries(fuaekt glfw ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})