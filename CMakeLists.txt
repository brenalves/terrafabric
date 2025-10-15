cmake_minimum_required(VERSION 3.20)

project(terrafabric)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(external/glfw)
add_subdirectory(external/glm)

add_executable(terrafabric
    src/main.cpp

    src/core/window.h src/core/window.cpp
    src/core/application.h src/core/application.cpp
    src/core/resourcemanager.h src/core/resourcemanager.cpp
    src/core/input.h src/core/input.cpp
    src/core/timer.h src/core/timer.cpp

    src/rendering/renderer.h src/rendering/renderer.cpp
    src/rendering/shader.h src/rendering/shader.cpp
    src/rendering/bufferlayout.h
    src/rendering/buffer.h
    src/rendering/vertexarray.h src/rendering/vertexarray.cpp
    src/rendering/texture.h src/rendering/texture.cpp

    src/components/transform.h
    src/components/camera.h
    src/components/mesh.h

    src/game/player.h src/game/player.cpp
    src/game/world.h src/game/world.cpp
    src/game/chunk.h src/game/chunk.cpp
    src/game/crosshair.h src/game/crosshair.cpp
    src/game/block.h
    src/game/ray.h
    src/game/raycast.h src/game/raycast.cpp

    external/glad/src/glad.c
    external/stb_image/src/stb_image.cpp
)

target_compile_definitions(terrafabric PRIVATE
    GLFW_INCLUDE_NONE
)

target_link_libraries(terrafabric PRIVATE
    glfw
)

target_include_directories(terrafabric PRIVATE
    src

    external/glfw/include
    external/glad/include
    external/glm
    external/stb_image/include
)

if(WIN32)
    target_link_libraries(terrafabric PRIVATE
        opengl32
    )
else()
    target_link_libraries(terrafabric PRIVATE
        GL
    )
endif()

add_custom_command(TARGET terrafabric POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:terrafabric>/assets
)