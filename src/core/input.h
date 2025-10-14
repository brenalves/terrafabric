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

    void setCursorMode(CursorMode mode);

    inline CursorMode getCursorMode() const { return _cursorMode; }
    inline float getMouseX() const { return _mouseX; }
    inline float getMouseY() const { return _mouseY; }

    inline static Input* getInstance() { return _instance; }
    
private:
    bool _currentKeyStates[GLFW_KEY_LAST];
    bool _previousKeyStates[GLFW_KEY_LAST];
    float _mouseX;
    float _mouseY;

    CursorMode _cursorMode;

    static Input* _instance;
};