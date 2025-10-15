#pragma once

#include <GLFW/glfw3.h>
#include <stdexcept>

enum CursorMode
{
    NORMAL = GLFW_CURSOR_NORMAL,
    HIDDEN = GLFW_CURSOR_HIDDEN,
    DISABLED = GLFW_CURSOR_DISABLED
};

class Input
{
public:
    Input();
    
    void updateStates();

    inline bool isKeyPressed(int key) const { return _currentKeyStates[key] && !_previousKeyStates[key]; }
    inline bool isKeyReleased(int key) const { return !_currentKeyStates[key] && _previousKeyStates[key]; }
    inline bool isKeyDown(int key) const { return _currentKeyStates[key]; }
    inline bool isKeyUp(int key) const { return !_currentKeyStates[key]; }
    inline bool isMouseButtonPressed(int button) const { return _currentMouseButtonStates[button] && !_previousMouseButtonStates[button]; }
    inline bool isMouseButtonReleased(int button) const { return !_currentMouseButtonStates[button] && _previousMouseButtonStates[button]; }
    inline bool isMouseButtonDown(int button) const { return _currentMouseButtonStates[button]; }
    inline bool isMouseButtonUp(int button) const { return !_currentMouseButtonStates[button]; }

    void setCursorMode(CursorMode mode);

    inline CursorMode getCursorMode() const { return _cursorMode; }
    inline float getMouseX() const { return _mouseX; }
    inline float getMouseY() const { return _mouseY; }

    inline static Input* getInstance() { return _instance; }
    
private:
    bool _currentKeyStates[GLFW_KEY_LAST];
    bool _previousKeyStates[GLFW_KEY_LAST];
    bool _currentMouseButtonStates[GLFW_MOUSE_BUTTON_LAST];
    bool _previousMouseButtonStates[GLFW_MOUSE_BUTTON_LAST];
    float _mouseX;
    float _mouseY;

    CursorMode _cursorMode;

    static Input* _instance;
};