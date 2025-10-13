cmake_minimum_required(VERSION 3.20)

project(terrafabric)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(external/glfw)
add_subdirectory(external/glm)

add_executable(terrafabric
    src/main.cpp

    src/core/window.h src/core/window.cpp
    src/core/application.h src/core/application.cpp
    src/core/renderer.h src/core/renderer.cpp
    src/core/resourcemanager.h src/core/resourcemanager.cpp

    src/rendering/shader.h src/rendering/shader.cpp
    src/rendering/bufferlayout.h
    src/rendering/buffer.h
    src/rendering/vertexarray.h src/rendering/vertexarray.cpp

    src/components/transform.h
    src/components/camera.h
    src/components/mesh.h

    src/game/player.h src/game/player.cpp
    src/game/quad.h src/game/quad.cpp

    external/glad/src/glad.c
)

target_link_libraries(terrafabric PRIVATE
    glfw
)

target_include_directories(terrafabric PRIVATE
    src

    external/glfw/include
    external/glad/include
    external/glm
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