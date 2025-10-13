#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <functional>

class Window
{
public:
    Window(int width, int height, const char* title);
    ~Window();

    void setOnCloseCallback(std::function<void()> callback);
    void setOnResizeCallback(std::function<void(int, int)> callback);

    void pollEvents();
    void swapBuffers();

    inline GLFWwindow* getPtr() const { return _ptr; }
    inline int getWidth() const { return _width; }
    inline int getHeight() const { return _height; }
    inline bool isVSync() const { return _vsync; }
    inline bool isFullscreen() const { return _fullscreen; }

private:
    GLFWwindow* _ptr;
    int _width;
    int _height;
    const char* _title;
    bool _vsync;
    bool _fullscreen;

    std::function<void()> _onCloseCallback;
    std::function<void(int, int)> _onResizeCallback;
};
