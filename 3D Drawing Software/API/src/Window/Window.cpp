#include "Window.h"
#include "../OpenGL/OpenGL.h"
#include "../PerspectiveCamera/PerspectiveCamera.h"
#include "../Core/ShaderArena/ShaderArena.h"

#include <iostream>
#include <chrono>

dra::Window::Window(int width, int height, double fps_limit, MultiSampling msaa) : m_Width(width), m_Height(height), m_FpsLimit(fps_limit), m_MSAA(msaa), m_Window(nullptr)
{
    if (!glfwInit()) {
        std::cerr << "Could not initialize glfw!" << std::endl;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, static_cast<int>(m_MSAA));

    m_Window = std::shared_ptr<GLFWwindow>(glfwCreateWindow(m_Width, m_Height, "Window Output", NULL, NULL), [] (GLFWwindow* window) {glfwDestroyWindow(window); });
    if (!m_Window)
    {
        glfwTerminate();
    }
    
    glfwMakeContextCurrent(m_Window.get());

    dra::OpenGL::Initialize();
    glEnable(0x809D);
    glViewport(0, 0, m_Width, m_Height);

    glfwSetFramebufferSizeCallback(m_Window.get(), [](GLFWwindow* window, int width, int height) { glViewport(0, 0, width, height); WindowEvents::SetResolution(width, height); });
    glfwSetScrollCallback(m_Window.get(), [](GLFWwindow* window, double xoffset, double yoffset) { WindowEvents::s_ScrollOffset = yoffset; });
}

dra::Window::~Window() {
    ShaderArena::Instance().TerminateArena();
    glfwTerminate();
}

void dra::Window::Run(Scene& scene)
{

    //dra::PerspectiveCamera camera(50.0, static_cast<float>(m_Width), static_cast<float>(m_Height), nullptr);
    //dra::Object focus(nullptr);
    //focus.GetTransform().SetLocalPosition(0.0f, -0.0f, -3.0f);
    //camera.SetParent(&focus);
    //camera.GetTransform().Translate(0.0f, -0.5f, 0.0f);

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

        mouse_click = glfwGetMouseButton(m_Window.get(), GLFW_MOUSE_BUTTON_RIGHT);

        accumulator += deltaTime;
        while (accumulator > 1000.0 / (m_FpsLimit + 1.0)) {
            accumulator -= 1000.0 / m_FpsLimit;

            // camera movement
            prev_mouse_x = mouse_x;
            prev_mouse_y = mouse_y;
            glfwGetCursorPos(m_Window.get(), &mouse_x, &mouse_y);
            scene.SendMousePosition(mouse_x, mouse_y);
            if (mouse_click == GLFW_PRESS) {
                scene.RotateMainCameraAroundFocus(/*(prev_mouse_y - mouse_y) / 5.0f, (prev_mouse_x - mouse_x) / 5.0f, 0.0f*/);
            }

            //Zoom
            scene.ZoomMainCamera(WindowEvents::s_ScrollOffset);
            WindowEvents::s_ScrollOffset = 0;
            if (WindowEvents::s_Reschange) {
                m_Width = WindowEvents::s_Width;
                m_Height = WindowEvents::s_Height;
                //camera = PerspectiveCamera(50.0, static_cast<float>(m_Width), static_cast<float>(m_Height), nullptr);
                WindowEvents::s_Reschange = false;
            }
            
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
