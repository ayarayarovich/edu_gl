#include "ShaderLoader.h"
#include "glad/gl.h"
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

unsigned int ShaderLoader::Compile(std::string_view vertexShaderText, std::string_view fragmentShaderText)
{
    const char *vertexShaderSource = vertexShaderText.data();
    const char *fragmentShaderSource = fragmentShaderText.data();

    int success;
    char infoLog[512];

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

std::pair<std::string, std::string>
ShaderLoader::Load(const std::filesystem::path &vertexShaderFile, const std::filesystem::path &fragmentShaderFile)
{
    std::ifstream vertexIfs(vertexShaderFile), fragmentIfs(fragmentShaderFile);
    if (!vertexIfs.is_open() || !fragmentIfs.is_open()) {
        std::cerr << "Failed to open shader files" << std::endl;
        return {};
    }

    std::string vertexShaderText, fragmentShaderText;

    std::stringstream ss;
    ss << vertexIfs.rdbuf();
    vertexShaderText = std::move(ss.str());

    ss.str("");
    ss << fragmentIfs.rdbuf();
    fragmentShaderText = std::move(ss.str());

    return {vertexShaderText, fragmentShaderText};
}

