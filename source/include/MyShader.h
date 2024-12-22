#pragma once
#include "glad/glad.h"
#include "glfw3.h"
#include "glm.hpp"
#include "gtc/type_ptr.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class MyShader
{
public:
  MyShader(const std::string &vertexPath, const std::string &fragmentPath);
  ~MyShader();
  void useShader();
  // 设置Uniform变量
  void setBool(const std::string &name, bool value) const;
  void setInt(const std::string &name, int value) const;
  void setFloat(const std::string &name, float value) const;
  void setVec4f(const std::string &name, const glm::vec4 vec4);

private:
  unsigned int m_programID;
  std::string readFile(const std::string &filePath);
  GLint compileShader(const std::string &shaderCode, GLenum shaderType);
  void checkCompileErrors(GLint shader, GLenum type);
};