#include <iostream>
#include <DrawApi.h>
#include <GLFW/glfw3.h>

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
    dra::Line line;
    line.Draw();

    glClearColor(0.8f, 0.3f, 0.2f, 1.0f);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }
    
    glfwTerminate();
	return 0;
}
