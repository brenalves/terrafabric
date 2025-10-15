#pragma once

#include <stdexcept>
#include <iostream>

#include "window.h"
#include "rendering/renderer.h"
#include "input.h"
#include "timer.h"

#include "game/player.h"
#include "game/world.h"
#include "game/crosshair.h"
#include "game/ray.h"

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
    Input* _input;
    Timer* _timer;
    
    Player* _player;
    World* _world;
    Crosshair* _crosshair;

    std::vector<Ray*> _rays;

    bool _isRunning;

    static Application* _instance;
};