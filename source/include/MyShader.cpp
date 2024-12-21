#include "MyShader.h"

MyShader::MyShader(const std::string &vertexPath, const std::string &fragmentPath)
{
  // 连着写:readFile().c_str()会引起生命周期问题
  std::string vertexCode = readFile(vertexPath);
  std::string fragmentCode = readFile(fragmentPath);
  const char *vertexCodeCstr = vertexCode.c_str();
  const char *fragmentCodeCstr = fragmentCode.c_str();

  GLint vertexShader = compileShader(vertexCodeCstr, GL_VERTEX_SHADER);
  GLint fragmentShader = compileShader(fragmentCodeCstr, GL_FRAGMENT_SHADER);

  m_programID = glCreateProgram();
  glAttachShader(m_programID, vertexShader);
  glAttachShader(m_programID, fragmentShader);
  glLinkProgram(m_programID);
  checkCompileErrors(m_programID, GL_LINK_STATUS);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

MyShader::~MyShader()
{
  glDeleteProgram(m_programID);
}

void MyShader::useShader()
{
  glUseProgram(m_programID);
}

void MyShader::setBool(const std::string &name, bool value) const
{
  glUniform1i(glGetUniformLocation(m_programID, name.c_str()), static_cast<int>(value));
}

void MyShader::setInt(const std::string &name, int value) const
{
  glUniform1i(glGetUniformLocation(m_programID, name.c_str()), value);
}

void MyShader::setFloat(const std::string &name, float value) const
{
  glUniform1f(glGetUniformLocation(m_programID, name.c_str()), value);
}

std::string MyShader::readFile(const std::string &filePath)
{
  std::ifstream shaderFile(filePath);
  if (!shaderFile.is_open())
  {
    std::cerr << "ERROR: Could not open file " << filePath << std::endl;
    return "";
  }
  std::stringstream buffer;
  buffer << shaderFile.rdbuf();
  shaderFile.close();

  return buffer.str();
}

GLint MyShader::compileShader(const std::string &shaderCode, GLenum shaderType)
{

  GLint shader = glCreateShader(shaderType);
  const char *shaderCodeCstr = shaderCode.c_str();
  glShaderSource(shader, 1, &shaderCodeCstr, NULL);
  glCompileShader(shader);
  checkCompileErrors(shader, shaderType);
  return shader;
}

void MyShader::checkCompileErrors(GLint object, GLenum type)
{
  GLint success;
  GLchar infoLog[1024];
  if (glIsShader(object))
  {

    // 检查着色器编译错误
    glGetShaderiv(object, GL_COMPILE_STATUS, &success);
    if (!success)
    {
      glGetShaderInfoLog(object, 1024, nullptr, infoLog);
      std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: "
                << (type == GL_VERTEX_SHADER ? "Vertex Shader" : "Fragment Shader")
                << "\n"
                << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
    }
  }

  else if (glIsProgram(object))
  {
    // 检查程序链接错误
    glGetProgramiv(object, GL_LINK_STATUS, &success);
    if (!success)
    {
      glGetProgramInfoLog(object, 1024, nullptr, infoLog);
      std::cerr << "ERROR::PROGRAM_LINKING_ERROR\n"
                << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
    }
  }
  else
  {
    // 未知类型
    std::cerr << "ERROR::UNKNOWN_TYPE_IN_CHECKCOMPILEERRORS" << std::endl;
  }
}
