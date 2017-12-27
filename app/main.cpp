#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "linmath.h"

#include "Scene.h"

#include <iostream>
using namespace std;

  GLfloat vertices[] = {
    -1.f, -1.f, 0.f,
     1.f,  -1.f, 0.f,
     0.f, 1.f, 0.f
  };

  GLfloat colors[] = {
    1.0f, 0.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f
  };

static const char* vertex_shader_text =
{
  "#version 400\n"\

  "layout(location=0) in vec3 in_Position;\n"\
  "layout(location=1) in vec4 in_Color;\n"\
  "uniform mat4 modelMat;\n"\
  "uniform mat4 viewMat;\n"\
  "uniform mat4 projMat;\n"\
  "out vec4 ex_Color;\n"\

  "void main(void)\n"\
  "{\n"\
  "  gl_Position = projMat * viewMat * modelMat * vec4(in_Position.x, in_Position.y, in_Position.z, 1.0);\n"\
  "  ex_Color = in_Color;\n"\
  "}\n"
};
static const char* fragment_shader_text =
{
  "#version 400\n"\

  "in vec4 ex_Color;\n"\
  "out vec4 out_Color;\n"\

  "void main(void)\n"\
  "{\n"\
  "  out_Color = ex_Color;\n"\
  "}\n"
};
static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}
int main(int argc, const char** argv)
{
    cout << "tfw application start" << endl;
    GLFWwindow* window;
    GLuint vertex_buffer, vertex_shader, fragment_shader, program;

    GLuint vaoId;
    GLuint colorBuffer;

    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        exit(EXIT_FAILURE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwSetKeyCallback(window, key_callback);
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    glfwSwapInterval(1);
    // NOTE: OpenGL error checks have been omitted for brevity

    // create the shader
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
    glCompileShader(vertex_shader);
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
    glCompileShader(fragment_shader);
    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    // create the vertex array
    glGenVertexArrays(1, &vaoId);
    glBindVertexArray(vaoId);

    // create the vbo
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // set vertex metadata for attributes (num elements, type, stride, offset)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);

    GLuint modelMatLocation = glGetUniformLocation(program, "modelMat");
    GLuint viewMatLocation = glGetUniformLocation(program, "viewMat");
    GLuint projMatLocation = glGetUniformLocation(program, "projMat");

    tfw::Scene scene;

    while (!glfwWindowShouldClose(window))
    {
        float ratio;
        int width, height;
        mat4x4 m, v, p;
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
        mat4x4_identity(m);
        mat4x4_identity(v);
        mat4x4_perspective(p,
                           1,
                           width / (float)height,
                           1.f, 60.0);
        glUseProgram(program);
            
        // move the eye back 2m
        mat4x4_translate(v, 0.f, 0.f, -2.f);
        // spin the model
        mat4x4_translate(m, -1.f, 0.f, -1.f);
        mat4x4_rotate_Y(m, m, (float) glfwGetTime());
        glUniformMatrix4fv(modelMatLocation, 1, GL_FALSE, (const GLfloat*) m);
        glUniformMatrix4fv(viewMatLocation, 1, GL_FALSE, (const GLfloat*) v);
        glUniformMatrix4fv(projMatLocation, 1, GL_FALSE, (const GLfloat*) p);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        scene.render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}