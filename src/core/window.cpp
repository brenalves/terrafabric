#include "window.h"

Window::Window(int width, int height, const char* title)
    : _width(width), _height(height), _title(title), _vsync(false), _fullscreen(false)
{
    // Initialize GLFW and create a window
    if (!glfwInit())
    {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    _ptr = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!_ptr)
    {
        throw std::runtime_error("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(_ptr);
    glfwSetWindowUserPointer(_ptr, this);
}

Window::~Window()
{
    if (_ptr)
    {
        glfwDestroyWindow(_ptr);
    }
    glfwTerminate();
}

void Window::setOnCloseCallback(std::function<void()> callback)
{
    _onCloseCallback = callback;

    glfwSetWindowCloseCallback(_ptr, [](GLFWwindow* window) {
        Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
        win->_onCloseCallback();
    });
}

void Window::setOnResizeCallback(std::function<void(int, int)> callback)
{
    _onResizeCallback = callback;

    glfwSetFramebufferSizeCallback(_ptr, [](GLFWwindow* window, int width, int height) {
        Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));

        win->_width = width;
        win->_height = height;

        win->_onResizeCallback(width, height);
    });
}

void Window::pollEvents()
{
    glfwPollEvents();
}

void Window::swapBuffers()
{
    glfwSwapBuffers(_ptr);
}
