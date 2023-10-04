#include <iostream>
#include <DrawApi.h>
#include <GLFW/glfw3.h>
#include <chrono>

int main() {

	GLFWwindow* window;

    if (!glfwInit()) {
        std::cerr << "Could not initialize glfw!" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(960, 540, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    dra::OpenGL::Initialize();

    std::cout << glGetString(GL_VERSION) << std::endl;
    {
        dra::ShaderArena::Instance().LoadShader("LineShader", "shaders/line.shader");

        dra::PerspectiveCamera camera(60, 960.0f, 540.0f);
        dra::Line line(&camera);

        auto currentTime = std::chrono::high_resolution_clock::now();
        auto oldTime = std::chrono::high_resolution_clock::now();
        auto deltaTime = std::chrono::duration<long double, std::milli>(currentTime - oldTime).count();

        long double accumulator = 0;

        GLCall(glClearColor(0.0f, 0.0f, 0.15f, 1.0f));
        while (!glfwWindowShouldClose(window)) {
            GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

            oldTime = currentTime;
            currentTime = std::chrono::high_resolution_clock::now();
            deltaTime = std::chrono::duration<long double, std::milli>(currentTime - oldTime).count();
            std::cout << deltaTime << std::endl;

            accumulator += deltaTime;
            while (accumulator > 1000.0 / 61.0) {
                accumulator -= 1000.0 / 60.0;
                line.Update();
                if (accumulator < (1000.0 / 59.0) - (1000.0 / 60.0)) accumulator = 0;
            }
            
            line.Draw();

            glfwSwapBuffers(window);

            glfwPollEvents();
        }
    }
    
    
    glfwTerminate();
	return 0;
}
