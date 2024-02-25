#include <iostream>
#include <DrawApi.h>
#include <GLFW/glfw3.h>
#include <chrono>

int main() {

    dra::Window window(960, 540, 120.0, dra::MultiSampling::x8);
    dra::Scene scene;
     
    std::cout << glGetString(GL_VERSION) << std::endl;
    {
        dra::Line line(nullptr);
        line.GetTransform().SetLocalPosition(0.0f, 0.0f, -3.0f);

        dra::Triangle triangle(nullptr);
        triangle.GetTransform().SetLocalPosition(-0.5f, -0.5f, -4.0f);
        triangle.GetTransform().Rotate(0.0f, 60.0f, -30.0f);

        dra::Triangle triangle1(nullptr);
        triangle1.GetTransform().SetLocalPosition(-0.5f, 1.0f, -2.0f);
        triangle1.GetTransform().Rotate(5.0f, 60.0f, -30.0f);

        dra::Triangle triangle2(nullptr);
        triangle2.GetTransform().SetLocalPosition(0.0f, 0.0f, -2.0f);
        triangle2.GetTransform().Rotate(26.0f, 33.0f, -30.0f);

        dra::Line line1(nullptr);
        line1.GetTransform().Rotate(0.0f, 0.0f, 45.0f);
        line1.GetTransform().SetLocalPosition(0.5f, 0.5f, -3.0f);

        dra::Line line2(nullptr);
        line2.GetTransform().SetLocalPosition(0.0f, 1.0f, -3.0f);

        dra::Line line3(nullptr);
        line3.GetTransform().Rotate(0.0f, 0.0f, 45.0f);
        line3.GetTransform().SetLocalPosition(-0.5f, 0.5f, -3.0f);

        dra::Line line4(nullptr);
        line4.GetTransform().Rotate(0.0f, 90.0f, 90.0f);
        line4.GetTransform().SetLocalPosition(-0.0f, 0.5f, -2.5f);

        scene.InsertRenderFunction([&](dra::Camera* camera) {
            line.Draw(camera);
            line1.Draw(camera);
            line2.Draw(camera);
            line3.Draw(camera);
            line4.Draw(camera);
            triangle.Draw(camera);
            triangle1.Draw(camera);
            triangle2.Draw(camera);
        });

        window.Run(scene);
    }
    ;
	return 0;
}
