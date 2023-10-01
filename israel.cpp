#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <format>

#include "ShaderLoader.h"

int main()
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_SAMPLES, 16);
    window = glfwCreateWindow(1100, 800, "Israel", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    int version = gladLoadGL(glfwGetProcAddress);
    if (version == 0) {
        std::cerr << "Failed to initialize OpenGL context\n";
        return -1;
    }

    std::cout << std::format("Loaded OpenGL {}.{}", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version)) << '\n';

    float vertices[] = {
            -1.0, 13.f/16, 0.0, // 0
             1.0, 13.f/16, 0.0, // 1
             1.0, 8.f/16,  0.0, // 2
            -1.0, 8.f/16,  0.0, // 3

            -1.0, -13.f/16, 0.0, // 4
             1.0, -13.f/16, 0.0, // 5
             1.0, -8.f/16,  0.0, // 6
            -1.0, -8.f/16,  0.0, // 7

             //Star
             0.0, 0.4325, 0.0, // 8
             0.0, 0.295, 0.0, // 9

             -0.272727, 0.2175, 0.0, // 10
              0.272727, 0.2175, 0.0, // 11

             -0.185454, 0.1457, 0.0, // 12
              0.185454, 0.1457, 0.0, // 13

              -0.185454, -0.1457, 0.0, // 14
              0.185454, -0.1457, 0.0, // 15

              -0.272727, -0.2175, 0.0, // 16
              0.272727, -0.2175, 0.0, // 17

              0.0, -0.295, 0.0, // 18
              0.0, -0.4325, 0.0, // 19
    };

    unsigned int indices[] = {
        0, 1, 2,
        0, 2, 3,

        4, 5, 6,
        4, 6, 7,

        10, 11, 13,
        10, 13, 12,

        10, 12, 18,
        10, 19, 18,

        11, 13, 18,
        11, 19, 18,

        8, 9, 14,
        8, 16, 14,

        8, 9, 15,
        8, 17, 15,

        16, 14, 17,
        17, 15, 14
    };

    glEnable(GL_MULTISAMPLE);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    auto [vertexShaderText, fragmentShaderText] = ShaderLoader::Load("shaders/simple.vert.glsl", "shaders/simple.frag.glsl");
    unsigned int shaderProgram = ShaderLoader::Compile(vertexShaderText, fragmentShaderText);

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glBindVertexArray(0);

    // reset
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDisableVertexAttribArray(0);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(1, 1, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(float), GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}