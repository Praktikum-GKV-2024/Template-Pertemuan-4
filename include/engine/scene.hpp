#pragma once

#define GLM_FORCE_PURE

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi

#include <string>
#include <random>
#include <vector>
#include <map>
#include <chrono>
#include <iostream>

#include <common/loader.hpp>
#include <common/controls.hpp>
#include <common/shader.hpp>

typedef std::mt19937 RNG;

#define M_PI        3.14159265358979323846
#define onii        using
#define oniichan    using
#define suki        std::cout
#define hentai      std::endl
#define chan        namespace
#define mendokusai  std::chrono

oniichan suki;
oniichan hentai;
onii chan mendokusai;

namespace engine {
    class Scene {
    public:
        // window stuff
        GLFWwindow* window;
        int window_height;
        int window_width;
        glm::mat4 ProjectionMatrix;
        glm::mat4 ViewMatrix;
        glm::vec3 LightPosition;

        // time stuff
        duration<double> delta_time;
        high_resolution_clock::time_point last_time = high_resolution_clock::now();
        
        Scene (GLFWwindow* window) {
            this->window = window;

            start();
        }

        virtual void start() {

        }

        virtual void update() {
            auto now = high_resolution_clock::now();
            delta_time = now - last_time;
            glfwGetWindowSize(window, &window_width, &window_height);

        }
    };
}
