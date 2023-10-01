#pragma once
#include <string>
#include <filesystem>

class ShaderLoader
{
  private:

  public:
    static std::pair<std::string, std::string> Load(const std::filesystem::path &vertexShaderFile, const std::filesystem::path &fragmentShaderFile);
    static unsigned int Compile(std::string_view vertexShaderText, std::string_view fragmentShaderText);
};
