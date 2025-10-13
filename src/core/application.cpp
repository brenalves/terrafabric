#include "application.h"

Application* Application::_instance = nullptr;

Application::Application()
{
    if(_instance != nullptr)
    {
        throw std::runtime_error("Application instance already exists!");
    }

    _instance = this;
    _isRunning = true;

    _window = new Window(800, 600, "Terrafabric");
    _window->setOnCloseCallback(std::bind(&Application::onCloseCallback, this));
    _window->setOnResizeCallback(std::bind(&Application::onResizeCallback, this, std::placeholders::_1, std::placeholders::_2));

    _renderer = new Renderer();

    _player = new Player();
    _player->getTransform().position = glm::vec3(0.0f, 0.0f, 3.0f);
    _player->getTransform().rotation = glm::vec3(0.0f, -90.0f, 0.0f);

    _quad = new Quad();
    _quad->getTransform().position = glm::vec3(0.0f, 0.0f, -3.0f);
}

Application::~Application()
{
    delete _quad;
    delete _player;
    delete _renderer;
    delete _window;

    _instance = nullptr;
}

void Application::run()
{
    while (_isRunning)
    {
        _window->pollEvents();

        _player->update();
        _quad->update();

        _renderer->clear();

        // render here
        _renderer->beginFrame(_player->getTransform(), _player->getCamera());
        _renderer->drawQuad(_quad->getTransform(), _quad->getMesh());

        _window->swapBuffers();
    }
}

void Application::onCloseCallback()
{
    std::cout << "Closing application..." << std::endl;
    _isRunning = false;
}

void Application::onResizeCallback(int width, int height)
{
    std::cout << "Window resized to " << width << "x" << height << std::endl;
    _renderer->onResize(width, height);
}
