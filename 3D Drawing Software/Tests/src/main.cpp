#include <iostream>
#include <DrawApi.h>
#include <GLFW/glfw3.h>
#include <chrono>

int main() {

    dra::Window window(960, 540, 120.0, dra::MultiSampling::x8);
    dra::Scene scene;
     
    std::cout << glGetString(GL_VERSION) << std::endl;
    {
        dra::Line line;
        line.GetTransform().SetLocalPosition(0.0f, 0.0f, 0.0f);

        dra::Triangle triangle;
        triangle.GetTransform().SetLocalPosition(-0.5f, -0.5f, -1.0f);
        triangle.GetTransform().Rotate(0.0f, 60.0f, -30.0f);

        dra::Triangle triangle1;
        triangle1.GetTransform().SetLocalPosition(-0.5f, 1.0f, 1.0f);
        triangle1.GetTransform().Rotate(5.0f, 60.0f, -30.0f);

        dra::Triangle triangle2;
        triangle2.GetTransform().SetLocalPosition(0.0f, 0.0f, 1.0f);
        triangle2.GetTransform().Rotate(26.0f, 33.0f, -30.0f);

        dra::Line line1;
        line1.GetTransform().Rotate(0.0f, 0.0f, 45.0f);
        line1.GetTransform().SetLocalPosition(0.5f, 0.5f, 0.0f);

        dra::Line line2;
        line2.GetTransform().SetLocalPosition(0.0f, 1.0f, 0.0f);

        dra::Line line3;
        line3.GetTransform().Rotate(0.0f, 0.0f, 45.0f);
        line3.GetTransform().SetLocalPosition(-0.5f, 0.5f, 0.0f);

        dra::Line line4;
        line4.GetTransform().Rotate(0.0f, 90.0f, 90.0f);
        line4.GetTransform().SetLocalPosition(-0.0f, 0.5f, 0.5f);

        dra::Point point0;
        point0.GetTransform().SetLocalPosition(-0.0f, 0.5f, 1.0f);

        //point0.GetTransform().SetLocalScale(10.0f, 10.0f, 10.0f);

        scene.InsertRenderFunction([&](dra::Camera* camera) {
            line.Draw(camera);
            line1.Draw(camera);
            line2.Draw(camera);
            line3.Draw(camera);
            line4.Draw(camera);
            triangle.Draw(camera);
            triangle1.Draw(camera);
            triangle2.Draw(camera);
            point0.Draw(camera);
        });

        window.Run(scene);
    }
    ;
	return 0;
}
