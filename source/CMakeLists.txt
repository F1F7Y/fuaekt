add_executable(fuaekt
               core/core.c
               core/error.c
               entities/player.c
               filesystem/filesystem.c
               input/input.c
               map/map.c
               material/material.c
               material/shader.c
               physics/physics.c
               renderer/renderer.c
               renderer/window.c
               utils/math.c
               main.c
              )

target_link_libraries(fuaekt glfw ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} m)