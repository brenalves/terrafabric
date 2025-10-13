#pragma once

#include <stdexcept>
#include <iostream>

#include "window.h"
#include "renderer.h"

#include "game/player.h"
#include "game/quad.h"

class Application
{
public:
    Application();
    ~Application();

    void run();

    inline Window* getWindow() const { return _window; }
    inline Player* getPlayer() const { return _player; }

    inline static Application* getInstance() { return _instance; }

private:
    void onCloseCallback();
    void onResizeCallback(int width, int height);

private:
    Window* _window;
    Renderer* _renderer;
    
    Player* _player;
    Quad* _quad;

    bool _isRunning;

    static Application* _instance;
};