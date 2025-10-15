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
    _window->setVSync(false);

    _renderer = new Renderer();
    _input = new Input();
    _timer = new Timer();

    _player = new Player();
    _player->getTransform().position = glm::vec3(0.0f, 0.0f, 3.0f);
    _player->getTransform().rotation = glm::vec3(0.0f, -90.0f, 0.0f);

    _world = new World();
    _world->generateInitialChunks();

    _crosshair = new Crosshair();
}

Application::~Application()
{
    for(Ray* ray : _rays)
    {
        delete ray;
    }
    _rays.clear();

    delete _crosshair;
    delete _world;
    delete _player;

    ResourceManager::shutdown();

    delete _timer;
    delete _input;
    delete _renderer;
    delete _window;

    _instance = nullptr;
}

void Application::run()
{
    while (_isRunning)
    {
        _window->pollEvents();

        _input->updateStates();
        _timer->update();

        _player->update();
        _world->update();
        _crosshair->update();

        if(_input->isKeyPressed(GLFW_KEY_ESCAPE))
            onCloseCallback();

        if(_input->isKeyPressed(GLFW_KEY_F1))
        {
            if(_input->getCursorMode() == NORMAL)
                _input->setCursorMode(DISABLED);
            else
                _input->setCursorMode(NORMAL);
        }

        if(_input->isKeyPressed(GLFW_KEY_F2))
        {
            if(_renderer->getDrawMode() == DrawMode::FILL)
                _renderer->setDrawMode(DrawMode::LINE);
            else if(_renderer->getDrawMode() == DrawMode::LINE)
                _renderer->setDrawMode(DrawMode::POINT);
            else
                _renderer->setDrawMode(DrawMode::FILL);
        }

        if(_input->isKeyPressed(GLFW_KEY_F11))
        {
            // _window->setFullscreen(!_window->isFullscreen());
        }

        if(_input->isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
        {
            Ray* ray = new Ray;
            ray->origin = _player->getTransform().position;
            ray->direction = _player->getTransform().forward;
            ray->color = glm::vec3(1.0f, 0.0f, 0.0f);
            _rays.push_back(ray);
        }
        if(_input->isMouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT))
        {
            Ray* ray = new Ray;
            ray->origin = _player->getTransform().position;
            ray->direction = _player->getTransform().forward;
            ray->color = glm::vec3(0.0f, 1.0f, 0.0f);
            _rays.push_back(ray);
        }

        _renderer->clear();

        // render here
        _renderer->beginFrame(_player->getTransform(), _player->getCamera());

        auto chunks = _world->getChunks();
        for (auto chunk : chunks)
        {
            _renderer->drawChunk(chunk.first, chunk.second->getMesh());
        }

        for(Ray* ray : _rays)
        {
            _renderer->drawRay(ray->origin, ray->direction, 10.0f, ray->color);
        }

        _renderer->drawSprite(_crosshair->getTransform(), _crosshair->getTexture());

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
    _player->onResize(width, height);
}
