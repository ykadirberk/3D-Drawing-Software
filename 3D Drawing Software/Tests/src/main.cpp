#include <iostream>
#include <DrawApi.h>
#include <GLFW/glfw3.h>
#include <chrono>

int main() {

    dra::Window window(1280, 720, 120.0, dra::MultiSampling::x8);
    dra::Scene scene;
    
    {
        dra::Line line;
        line.GetTransform().SetLocalPosition(0.0f, 0.0f, 0.0f);

        /*dra::Triangle triangle;
        triangle.GetTransform().SetLocalPosition(-0.5f, -0.5f, -1.0f);
        triangle.GetTransform().Rotate(0.0f, 60.0f, -30.0f);

        dra::Triangle triangle1;
        triangle1.GetTransform().SetLocalPosition(-0.5f, 1.0f, 1.0f);
        triangle1.GetTransform().Rotate(5.0f, 60.0f, -30.0f);

        dra::Triangle triangle2;
        triangle2.GetTransform().SetLocalPosition(0.0f, 0.0f, 1.0f);
        triangle2.GetTransform().Rotate(26.0f, 33.0f, -30.0f);*/

        dra::Line line1;
        line1.GetTransform().Rotate(0.0f, 0.0f, 90.0f);
        line1.GetTransform().SetLocalPosition(0.5f, 0.5f, 0.0f);

        dra::Line line2;
        line2.GetTransform().SetLocalPosition(0.0f, 1.0f, 0.0f);

        dra::Line line3;
        line3.GetTransform().Rotate(0.0f, 0.0f, 90.0f);
        line3.GetTransform().SetLocalPosition(-0.5f, 0.5f, 0.0f);

        dra::Line line4;
        line4.GetTransform().Rotate(0.0f, 90.0f, 0.0f);
        line4.GetTransform().SetLocalPosition(-0.0f, 0.5f, 0.5f);

        dra::Point point0;
        point0.GetTransform().SetLocalPosition(-0.0f, 0.5f, 1.0f);

        dra::Point point1;
        point1.GetTransform().SetLocalPosition(-0.0f, 0.5f, 0.0f);

        dra::Point point2;
        point2.GetTransform().SetLocalPosition(-0.5f, 0.0f, 0.0f);

        dra::Point point3;
        point3.GetTransform().SetLocalPosition(0.5f, 0.0f, 0.0f);

        dra::Point point4;
        point4.GetTransform().SetLocalPosition(-0.5f, 1.0f, 0.0f);

        dra::Point point5;
        point5.GetTransform().SetLocalPosition(0.5f, 1.0f, 0.0f);

        //point0.GetTransform().SetLocalScale(5.0f, 5.0f, 5.0f);

        dra::Point center;
        center.GetTransform().Translate(-3.0f, 0.0f,0.0f);

        dra::Line arm;
        arm.GetTransform().Rotate(0.0f, 0.0f, 0.0f);
        arm.GetTransform().Translate(-3.0f,0.0f,0.0f);

        arm.SetParent(&center);

        dra::PolygonalSurface surface(
            { 
                {-0.5f, -0.5f},
                { 0.5f, -0.5f},
                { 0.5f,  0.5f},
                {-0.5f,  0.5f}
            }, 
        0.025);
        surface.GetTransform().SetLocalPosition(0.0f, 0.5f, 0.0f);
        

        dra::Sphere sph(50);
        sph.GetTransform().SetLocalPosition(-1.0f, 0.5f, -0.5f);
        sph.GetTransform().SetLocalScale(0.5f, 0.5f, 0.5f);

        dra::Cube cube;
        cube.GetTransform().SetLocalScale(0.5f, 0.5f, 0.5f);
        cube.GetTransform().SetLocalPosition(1.0f, 0.5f, 0.5f);

        dra::Pyramid pyd;
        pyd.GetTransform().SetLocalScale(0.5f, 0.5f, 0.5f);
        
        dra::Cone cn(50);
        cn.GetTransform().SetLocalPosition(0.0f, 0.5f, 0.0f);
        cn.GetTransform().SetLocalScale(0.5f, 0.5f, 0.5f);

        /*dra::Line seline(glm::vec3(0.0f, 0.5f, 0.0f), glm::vec3(1.0f, 1.0f, -1.0f));
        dra::Point selinepoint;
        selinepoint.GetTransform().Translate(1.0f, 1.0f, -1.0f);*/

        const float pi = std::cos(-1);
        float pos = 0.0f;

        scene.InsertUpdateFunction( [&]() {
            pos += 3.0f;
            center.GetTransform().Rotate(0.0f, 0.00f, 3.0f);
            center.GetTransform().SetLocalPosition(std::sin(pos * pi / 180.0f), 0.5f - std::cos(pos * pi / 180.0f), std::sin(pos * pi / 180.0f));
        });

        scene.InsertUpdateFunction([&]() {
            surface.GetTransform().Rotate(0.5f, 1.1f, 0.0f);
            sph.GetTransform().Translate( std::sin(pos * pi / 180.0f) / 100.0f, std::cos(pos * pi / 180.0f) / 100.0f, 0.0f);
        });

        scene.InsertUpdateFunction([&]() {
            cube.GetTransform().SetLocalPosition(1.0f, 0.5f - std::cos(pos * pi / 180.0f), std::sin(pos* pi / 180.0f));
            cube.GetTransform().Rotate(0.0f, 0.0f, 1.0f);
        });

        scene.InsertUpdateFunction([&]() {
            pyd.GetTransform().SetLocalPosition(-1.0f, 0.5f - std::cos(pos * pi / 180.0f), std::sin(pos* pi / 180.0f));
            pyd.GetTransform().Rotate(0.0f, 0.0f, -1.0f);
        });

        scene.InsertUpdateFunction([&]() {
            cn.GetTransform().SetLocalPosition(0.0f, -std::cos(pos * pi / 180.0f) * 3, std::sin(pos * pi / 180.0f));
            cn.GetTransform().Rotate(0.0f, 0.0f, -1.0f);
        });

        scene.InsertRenderFunction([&](dra::Camera* camera) {
            line.Draw(camera);
            line1.Draw(camera);
            line2.Draw(camera);
            line3.Draw(camera);
            line4.Draw(camera);
            
            point0.Draw(camera);
            point1.Draw(camera);
            point2.Draw(camera);
            point3.Draw(camera);
            point4.Draw(camera);
            point5.Draw(camera);
            //
            surface.Draw(camera);
            sph.Draw(camera);
            pyd.Draw(camera);

            cn.Draw(camera);

            /*seline.Draw(camera);
            selinepoint.Draw(camera);*/
            
            cube.Draw(camera);
            //
            center.Draw(camera);
            arm.Draw(camera);
        });

        window.Run(scene);
    }
    
	return 0;
}
