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
        dra::OrthogonalCamera camera(960.0f, 540.0f, nullptr);
        dra::Object center( nullptr);
        center.GetTransform().SetLocalPosition(0.0f, -0.0f, -3.0f);

        camera.SetParent(&center);
        camera.GetTransform().Translate(0.0f, -0.5f, 0.0f);

        dra::Line line(&camera, nullptr);
        line.GetTransform().SetLocalPosition(0.0f, 0.0f, -3.0f);

        dra::Line line1(&camera, nullptr);
        line1.GetTransform().Rotate(0.0f, 0.0f, 90.0f);
        line1.GetTransform().SetLocalPosition(0.5f, 0.5f, -3.0f);

        dra::Line line2(&camera, nullptr);
        line2.GetTransform().SetLocalPosition(0.0f, 1.0f, -3.0f);

        dra::Line line3(&camera, nullptr);
        line3.GetTransform().Rotate(0.0f, 0.0f, 90.0f);
        line3.GetTransform().SetLocalPosition(-0.5f, 0.5f, -3.0f);

        dra::Line line4(&camera, nullptr);
        line4.GetTransform().Rotate(0.0f, 90.0f, 90.0f);
        line4.GetTransform().SetLocalPosition(-0.0f, 0.5f, -2.5f);

        auto currentTime = std::chrono::high_resolution_clock::now();
        auto oldTime = std::chrono::high_resolution_clock::now();
        auto deltaTime = std::chrono::duration<long double, std::milli>(currentTime - oldTime).count();

        long double accumulator = 0;

        int mouse_click = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);
        double mouse_x, mouse_y, prev_mouse_x, prev_mouse_y;
        glfwGetCursorPos(window, &mouse_x, &mouse_y);

        GLCall(glClearColor(0.0f, 0.0f, 0.15f, 1.0f));
        while (!glfwWindowShouldClose(window)) {

            oldTime = currentTime;
            currentTime = std::chrono::high_resolution_clock::now();
            deltaTime = std::chrono::duration<long double, std::milli>(currentTime - oldTime).count();

            mouse_click = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);

            accumulator += deltaTime;
            while (accumulator > 1000.0 / 61.0) {
                accumulator -= 1000.0 / 60.0;
                //line.Update();

                prev_mouse_x = mouse_x;
                prev_mouse_y = mouse_y;
                glfwGetCursorPos(window, &mouse_x, &mouse_y);
                if (mouse_click == GLFW_PRESS) {
                    center.GetTransform().Rotate((mouse_y - prev_mouse_y) / 5, (mouse_x - prev_mouse_x) / 5, 0.0f);
                }

                //auto campos = camera.GetTransform().GetWorldPosition();
                //auto linepos = line.GetTransform().GetWorldPosition();
                //std::cout << "CamPos:(" << campos.x << ", " << campos.y << ", " << campos.z << ")\n";
                //std::cout << "linepos:(" << linepos.x << ", " << linepos.y << ", " << linepos.z << ")\n";
                if (accumulator < (1000.0 / 59.0) - (1000.0 / 60.0)) accumulator = 0;
            }

            GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
            
            line.Draw();
            line1.Draw();
            line2.Draw();
            line3.Draw();
            line4.Draw();

            glfwSwapBuffers(window);

            glfwPollEvents();
        }
    }
    
    dra::ShaderArena::Instance().TerminateArena();
    glfwTerminate();
	return 0;
}
