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
        dra::PerspectiveCamera camera(60, 960.0f, 540.0f, nullptr);
        dra::Object center( nullptr);
        center.GetTransform().SetLocalPosition(0.0f, -0.5f, -3.0f);
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

        GLCall(glClearColor(0.0f, 0.0f, 0.15f, 1.0f));
        while (!glfwWindowShouldClose(window)) {

            oldTime = currentTime;
            currentTime = std::chrono::high_resolution_clock::now();
            deltaTime = std::chrono::duration<long double, std::milli>(currentTime - oldTime).count();

            accumulator += deltaTime;
            while (accumulator > 1000.0 / 61.0) {
                accumulator -= 1000.0 / 60.0;
                //line.Update();
                center.GetTransform().Rotate(0.0f, 1.0f, 0.0f);
                auto pos = camera.GetTransform().GetWorldPosition();
                auto cent_pos = center.GetTransform().GetWorldPosition();
                std::cout << "Camera:(\t" << pos.x << ",\t" << pos.y << ",\t" << pos.z << ")\tCenter:(" << cent_pos.x << ",\t" << cent_pos.y << ",\t" << cent_pos.z << ")" << std::endl;
                /*auto rot = camera.GetTransform().GetWorldRotation();
                std::cout << "Camera Rot x=" << rot.x << ", y=" << rot.y << ", z=" << rot.z << std::endl;*/
                //camera.GetTransform().Rotate(0.0f, 1.0f, 0.0f);
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
