#pragma once

#include <GLFW/glfw3.h>
#include <stdexcept>

class Input
{
public:
    Input();
    
    void updateStates();

    inline bool isKeyPressed(int key) const { return _currentKeyStates[key] && !_previousKeyStates[key]; }
    inline bool isKeyReleased(int key) const { return !_currentKeyStates[key] && _previousKeyStates[key]; }
    inline bool isKeyDown(int key) const { return _currentKeyStates[key]; }
    inline bool isKeyUp(int key) const { return !_currentKeyStates[key]; }

    inline static Input* getInstance() { return _instance; }
    
private:
    bool _currentKeyStates[GLFW_KEY_LAST];
    bool _previousKeyStates[GLFW_KEY_LAST];

    static Input* _instance;
};