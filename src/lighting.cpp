#define GLM_FORCE_PURE

#include <GLFW/glfw3.h>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi
#include <iostream>
#include <cmath>
#include <vector>
#include <cstring>
#include <common/controls.hpp>
#include <common/shader.hpp>
#include <engine/scene.hpp>
#include <engine/object.hpp>

enum class CAMERA_MODE{
    PROJECTION_1,
    PROJECTION_2,
    PROJECTION_3,
    LIGHT,
    FREE_VIEW,
};

class MainScene : engine::Scene {
public:
    GLFWwindow* window;
    engine::Object *barrel, *cube_2, *cube_3, *plane;
    CAMERA_MODE camera_mode = CAMERA_MODE::PROJECTION_1;       

    MainScene (GLFWwindow* window): Scene(window) {
        this->window = window;

        glClearColor(0.0f, 0.0f, 0.0f, 1.f);

        // Enable depth test
        glEnable(GL_DEPTH_TEST);

        // Accept fragment if it is closer to the camera than the former one
        glDepthFunc(GL_LEQUAL); 

        // Cull triangles which normal is not towards the camera
        glEnable(GL_CULL_FACE);

        // Blending
        glEnable(GL_BLEND);
        // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // Associate the object instance with the GLFW window
        glfwSetWindowUserPointer(window, this);

        start();
    }

    void start() override {
        // ======================== PLANE ========================

        // LOAD PLANE SHADERS AND MODEL
        GLuint shader = LoadShaders("res/shader/Textured_With_Light.vs", "res/shader/Textured_With_Light.fs");
        plane = new engine::Object("res/obj/plane.obj", "res/bmp/plane_tugas.bmp", shader, this);

        // ======================== BARREL ========================

        // LOAD BARREL MODEL
        shader = LoadShaders("res/shader/Textured_With_Light.vs", "res/shader/Textured_With_Light.fs");
        barrel = new engine::Object("res/obj/barrel.obj", "res/bmp/barrel.bmp", shader, this);

        barrel->transform = glm::translate(barrel->transform, vec3(4, 1, 1));

        LightPosition = vec3(0, 10, 0);

        // binding keys
        glfwSetKeyCallback(window, keyCallbackStatic);
    }

    void update() override {
        Scene::update();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        auto up = vec3( 0, 1, 0);
        auto aspect_ratio = (float)window_width/window_height;
        switch (camera_mode) {
            case CAMERA_MODE::PROJECTION_1:
                ViewMatrix = glm::lookAt(
                    vec3(0, 4, 5), // posisi kamera
                    vec3(4, 1, 1), // melihat barrel
                    up
                );
                ProjectionMatrix = glm::perspective<float>(glm::radians(45.f), aspect_ratio, 0.1f, 1000.0f);
                break;  
            case CAMERA_MODE::PROJECTION_2:
                ViewMatrix = glm::lookAt(
                    vec3(0, 1, 0), // posisi kamera
                    vec3(4, 1, 1), // melihat barrel
                    up
                );
                ProjectionMatrix = glm::perspective<float>(glm::radians(45.f), aspect_ratio, 0.1f, 1000.0f);
                break;
            case CAMERA_MODE::PROJECTION_3:
                ViewMatrix = glm::lookAt(
                    vec3(3, 2, 6), // posisi kamera
                    vec3(4, 1, 1), // melihat barrel
                    up
                );
                ProjectionMatrix = glm::perspective<float>(glm::radians(45.f), aspect_ratio, 0.1f, 1000.0f);
                break;
            case CAMERA_MODE::LIGHT:
                ViewMatrix = glm::lookAt(
                    vec3(0, 10, 0), // posisi kamera
                    vec3(4, 2, 1), // melihat barrel
                    up
                );
                ProjectionMatrix = glm::perspective<float>(glm::radians(45.f), aspect_ratio, 0.1f, 1000.0f);
                break;
            case CAMERA_MODE::FREE_VIEW:
                // Don't touch
                computeMatricesFromInputs(window);
                ViewMatrix = getViewMatrix();
                ProjectionMatrix = getProjectionMatrix();
                break;
        }

        
        barrel->render_with_projection();
        // cube_2->render_with_projection();
        // cube_3->render_with_projection();
        plane->render_with_projection();
    }

private:
    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
        if (action == GLFW_PRESS) {
            std::cout << key << std::endl;
            switch (key) {
            case GLFW_KEY_1:
                camera_mode = CAMERA_MODE::PROJECTION_1;
                break;
            case GLFW_KEY_2:
                camera_mode = CAMERA_MODE::PROJECTION_2;
                break;
            case GLFW_KEY_3:
                camera_mode = CAMERA_MODE::PROJECTION_3;
                break;
            case GLFW_KEY_9:
                camera_mode = CAMERA_MODE::LIGHT;
                break;
            case GLFW_KEY_0:
                camera_mode = CAMERA_MODE::FREE_VIEW;
                break;
            }
        }
    }

    static void keyCallbackStatic(GLFWwindow* window, int key, int scancode, int action, int mods) {
        MainScene* instance = static_cast<MainScene*>(glfwGetWindowUserPointer(window));
        instance->key_callback(window, key, scancode, action, mods);
    }
    

};