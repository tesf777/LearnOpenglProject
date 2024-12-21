#include "glad/glad.h"
#include "glfw3.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";

const char *fragmentShader1Source = "#version 330 core\n"
                                    "out vec4 FragColor;\n"
                                    "void main()\n"
                                    "{\n"
                                    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                    "}\0";
const char *fragmentShader2Source = "#version 330 core\n"
                                    "out vec4 FragColor;\n"
                                    "void main()\n"
                                    "{\n"
                                    "   FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
                                    "}\n\0";
int main()
{
  // glfw: initialize and configure
  // ------------------------------
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // glfw window creation
  // --------------------
  GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
  if (window == NULL)
  {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  // 设置本窗口为主上下文
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // glad: load all OpenGL function pointers
  // ---------------------------------------
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }
  //--------------------开始初始化着色器程序-----------------------
  unsigned int vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }

  unsigned int fragment1Shader;
  fragment1Shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment1Shader, 1, &fragmentShader1Source, NULL);
  glCompileShader(fragment1Shader);

  unsigned int fragment2Shader;
  fragment2Shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment2Shader, 1, &fragmentShader2Source, NULL);
  glCompileShader(fragment2Shader);

  unsigned int shader1Program;
  shader1Program = glCreateProgram();
  glAttachShader(shader1Program, vertexShader);
  glAttachShader(shader1Program, fragment1Shader);
  glLinkProgram(shader1Program);

  unsigned int shader2Program;
  shader2Program = glCreateProgram();
  glAttachShader(shader2Program, vertexShader);
  glAttachShader(shader2Program, fragment2Shader);
  glLinkProgram(shader2Program);

  glDeleteShader(vertexShader);
  glDeleteShader(fragment1Shader);
  glDeleteShader(fragment2Shader);
  //------------------至此着色器程序初始化完成----------------------

  float tri_1[] = {
      -0.5f, -0.5f, 0.0f,
      0.5f, -0.5f, 0.0f,
      0.0f, 0.5f, 0.0f};

  // 逆时针
  unsigned int tri_1_index[] = {0, 1, 2};

  unsigned int VAO_1;
  glGenVertexArrays(1, &VAO_1);
  glBindVertexArray(VAO_1);

  unsigned int VBO_1;
  glGenBuffers(1, &VBO_1);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_1);
  glBufferData(GL_ARRAY_BUFFER, sizeof(tri_1), tri_1, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  unsigned int EBO_1;
  glGenBuffers(1, &EBO_1);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_1);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(tri_1_index), tri_1_index, GL_STATIC_DRAW);

  float tri_2[] = {
      -0.5f, 0.5f, 0.0f,
      0.0f, -0.5f, 0.0f,
      0.5f, 0.5f, 0.0f};

  // 逆时针
  unsigned int tri_2_index[] = {0, 1, 2};

  unsigned int VAO_2;
  glGenVertexArrays(1, &VAO_2);
  glBindVertexArray(VAO_2);

  unsigned int VBO_2;
  glGenBuffers(1, &VBO_2);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_2);
  glBufferData(GL_ARRAY_BUFFER, sizeof(tri_2), tri_2, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  unsigned int EBO_2;
  glGenBuffers(1, &EBO_2);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_2);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(tri_2_index), tri_2_index, GL_STATIC_DRAW);

  // render loop
  // -----------
  while (!glfwWindowShouldClose(window))
  {
    // input
    // -----
    processInput(window);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(shader1Program);
    glBindVertexArray(VAO_1);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
    glUseProgram(shader2Program);
    glBindVertexArray(VAO_2);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    // -------------------------------------------------------------------------------
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glDeleteVertexArrays(1, &VAO_1);
  glDeleteBuffers(1, &VBO_1);
  glDeleteBuffers(1, &EBO_1);
  glDeleteVertexArrays(1, &VAO_2);
  glDeleteBuffers(1, &VBO_2);
  glDeleteBuffers(1, &EBO_2);
  glDeleteProgram(shader1Program);
  glDeleteProgram(shader2Program);

  // glfw: terminate, clearing all previously allocated GLFW resources.
  // ------------------------------------------------------------------
  glfwTerminate();
  return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
  // make sure the viewport matches the new window dimensions; note that width and
  // height will be significantly larger than specified on retina displays.
  glViewport(0, 0, width, height);
}