//
// Created by maxim on 05.03.2020.
//

#ifndef FIRST_IO_H
#define FIRST_IO_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Camera.h>

//
// Created by maxim on 05.03.2020.
//

#include "io.h"

#define WIDTH 1000
#define HEIGHT 800

static bool pressed = false;
static int key_ = 0;
static int act = 0;
static int m = 0;

static bool resized = true;
static int new_w = WIDTH;
static int new_h = HEIGHT;

class IO {
public:
    IO(int w, int h, const char *t, Camera *cam) : width(w), height(h), title(t), camera(cam) {
        initGLFW();
        createWindow();
        screen = new Screen{};
    }

    bool closed() const {
        return glfwWindowShouldClose(window);
    }

    IO(const char *t, Camera *cam) : IO(WIDTH, HEIGHT, t, cam) {}

    void draw(const unsigned char *im, int width_i, int height_i) {
        glfwPollEvents();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        if (resized) on_resize(width_i, height_i);
        if (pressed) on_press();

        screen->drawTexture(im, width_i, height_i);

        glfwSwapBuffers(window);
    }

    ~IO() {
        delete screen;
        glfwTerminate();
    }

private:
    struct Screen {
        GLuint VAO, VBO, EBO, texture;
        Shader *shader;
        constexpr static GLfloat vertices[] = {
                1.0f, 1.0f, 1.0f, 1.0f, // Top Right
                1.0f, -1.0f, 1.0f, 0.0f, // Bottom Right
                -1.0f, -1.0f, 0.0f, 0.0f, // Bottom Left
                -1.0f, 1.0f, 0.0f, 1.0f  // Top Left
        };
        constexpr static GLuint indices[] = {  // Note that we start from 0!
                0, 1, 2, // First Triangle
                0, 2, 3  // Second Triangle
        };

        Screen() : VAO{}, VBO{}, EBO{}, texture{} {
            shader = new Shader("../shaders/vertexsh", "../shaders/fragmentsh");
            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);
            glGenBuffers(1, &EBO);

            glBindVertexArray(VAO);

            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

            // Position attribute
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid *) 0);
            glEnableVertexAttribArray(0);
            // Color attribute
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid *) (2 * sizeof(GLfloat)));
            glEnableVertexAttribArray(1);

            glBindVertexArray(0);

            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glBindTexture(GL_TEXTURE_2D, 0);
        };

        void drawTexture(const unsigned char *image, int width, int height) {
            //
            glm::mat4 scale(1);
//            scale = glm::scale(scale, glm::vec3(4, 4, 0));
            GLint scaleloc = glGetUniformLocation(shader->Program, "scale");


            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
            shader->Use();

            glUniformMatrix4fv(scaleloc, 1, GL_FALSE, glm::value_ptr(scale));

            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);

            glBindTexture(GL_TEXTURE_2D, 0);
        }

        ~Screen() {
            delete shader;
            glDeleteVertexArrays(1, &VAO);
            glDeleteBuffers(1, &VBO);
            glDeleteBuffers(1, &EBO);
        }
    };

    void initGLFW() {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    }

    void createWindow() {
        window = glfwCreateWindow(width, height, title, nullptr, nullptr);
        if (window == nullptr) {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
        }
        glfwMakeContextCurrent(window);
        glfwSetKeyCallback(window, key_callback);
        glfwSetWindowSizeCallback(window, window_size_callback);
        glewExperimental = GL_TRUE;
        glewInit();
        glViewport(0, 0, width, height);
    }

    static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode) {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GL_TRUE);
        else {
            key_ = key;
            act = action;
            m = mode;
            pressed = true;
        }
    }

    void on_press() {
        camera->move(key_, act, m);
        pressed = false;
    }

    static void window_size_callback(GLFWwindow *window, int w, int h) {
        resized = true;
        new_w = w;
        new_h = h;
    }

    void on_resize(int width_i, int height_i) {
        if (resized) {
            width = new_w;
            height = new_h;
        }

        int x = 0, y = 0, a = 0, b = 0;
        if ((float) height_i / width_i > (float) height / width) {
            a = width_i * height / height_i;
            b = height;
            x = std::max(0, width - a) / 2;
        } else {
            a = width;
            b = height_i * width / width_i;
            y = std::max(0, height - b) / 2;
        }

        glViewport(x, y, a, b);
        resized = false;
    }

    const char *title;
    unsigned char *image;
    int width, height;
    GLFWwindow *window;
    Screen *screen;
    Camera *camera;
};


#endif //FIRST_IO_H
