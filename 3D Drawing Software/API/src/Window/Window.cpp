#include "Window.h"
#include "../OpenGL/OpenGL.h"
#include <iostream>
#include <chrono>

dra::Window::Window() : m_FpsLimit(120.0), m_Window(nullptr)
{
    if (!glfwInit()) {
        std::cerr << "Could not initialize glfw!" << std::endl;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_Window = std::shared_ptr<GLFWwindow>(glfwCreateWindow(960, 540, "Hello World", NULL, NULL));
    if (!m_Window)
    {
        glfwTerminate();
    }
    glfwMakeContextCurrent(m_Window.get());

    dra::OpenGL::Initialize();
}

dra::Window::~Window()
{
}

void dra::Window::Run(const Scene& scene)
{
    auto currentTime = std::chrono::high_resolution_clock::now();
    auto oldTime = std::chrono::high_resolution_clock::now();
    auto deltaTime = std::chrono::duration<long double, std::milli>(currentTime - oldTime).count();

    long double accumulator = 0;

    int mouse_click = glfwGetMouseButton(m_Window.get(), GLFW_MOUSE_BUTTON_RIGHT);
    double mouse_x, mouse_y, prev_mouse_x, prev_mouse_y;
    glfwGetCursorPos(m_Window.get(), &mouse_x, &mouse_y);
    glClearColor(0.0f, 0.0f, 0.15f, 1.0f);
    while (!glfwWindowShouldClose(m_Window.get())) {

        oldTime = currentTime;
        currentTime = std::chrono::high_resolution_clock::now();
        deltaTime = std::chrono::duration<long double, std::milli>(currentTime - oldTime).count();

        accumulator += deltaTime;
        while (accumulator > 1000.0 / (m_FpsLimit + 1.0)) {
            accumulator -= 1000.0 / m_FpsLimit;

            scene.RunUpdates();

            if (accumulator < (1000.0 / (m_FpsLimit - 1.0)) - (1000.0 / m_FpsLimit)) accumulator = 0;
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //draws here
        scene.RunRenders();

        glfwSwapBuffers(m_Window.get());

        glfwPollEvents();
    }
}
