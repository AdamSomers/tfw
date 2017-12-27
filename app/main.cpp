// from glfw
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "linmath.h"

// from yocto
#include <yocto_gl.h>

#include "Scene.h"

#include <iostream>
using namespace std;

struct Tri {
    GLfloat vertices[9] = {
        -1.f, -1.f, 0.2f,
        1.f,  -1.f, 0.2f,
        0.f, 1.f, 0.2f
    };

    GLfloat colors[12] = {
        1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
    };

    GLfloat uvs[6] = {
        .5f, 0.f,
        0.f, 1.f,
        1.f, 1.f
    };
    GLuint vertBuf, colorBuf, uvBuf;
};

struct Quad {
    GLfloat vertices[18] = {
        -1.f, -1.f, 0.f,
        1.f,  -1.f, 0.f,
        -1.f, 1.f, 0.f,
        -1.f, 1.f, 0.f,
        1.f,  -1.f, 0.f,
        1.f, 1.f, 0.f
    };

    GLfloat colors[24] = {
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f
    };

    GLfloat uvs[12] = {
        0.f, 1.f,
        1.f, 1.f,
        0.f, 0.f,
        0.f, 0.f,
        1.f, 1.f,
        1.f, 0.f
    };
    GLuint vertBuf, colorBuf, uvBuf;
};

static const char* vertex_shader_text =
{
    "#version 400\n"\
    
    "layout(location=0) in vec3 in_Position;\n"\
    "layout(location=1) in vec4 in_Color;\n"\
    "layout(location=2) in vec2 in_uv;\n"\
    "uniform mat4 modelMat;\n"\
    "uniform mat4 viewMat;\n"\
    "uniform mat4 projMat;\n"\
    "out vec4 ex_Color;\n"\
    "out vec2 ex_uv;\n"\
    
    "void main(void)\n"\
    "{\n"\
    "  gl_Position = projMat * viewMat * modelMat * vec4(in_Position.x, in_Position.y, in_Position.z, 1.0);\n"\
    "  ex_Color = in_Color;\n"\
    "  ex_uv = in_uv;\n"\
    "}\n"
};
static const char* fragment_shader_text =
{
    "#version 400\n"\
    
    "in vec4 ex_Color;\n"\
    "in vec2 ex_uv;\n"\
    "out vec4 out_Color;\n"\
    "uniform sampler2D tex;\n"\
    
    "void main(void)\n"\
    "{\n"\
    "  out_Color = texture(tex, ex_uv) * ex_Color;\n"\
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
    
    GLuint triVaoId, quadVaoId;
    GLuint colorBuffer;
    GLuint uvBuffer;
    
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
    glGenVertexArrays(1, &triVaoId);
    glBindVertexArray(triVaoId);
    
    // create the vbo
    Tri tri;
    glGenBuffers(1, &tri.vertBuf);
    glBindBuffer(GL_ARRAY_BUFFER, tri.vertBuf);
    glBufferData(GL_ARRAY_BUFFER, sizeof(tri.vertices), tri.vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);
    glGenBuffers(1, &tri.colorBuf);
    glBindBuffer(GL_ARRAY_BUFFER, tri.colorBuf);
    glBufferData(GL_ARRAY_BUFFER, sizeof(tri.colors), tri.colors, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);
    glGenBuffers(1, &tri.uvBuf);
    glBindBuffer(GL_ARRAY_BUFFER, tri.uvBuf);
    glBufferData(GL_ARRAY_BUFFER, sizeof(tri.uvs), tri.uvs, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(2);

    Quad quad;
    glGenVertexArrays(1, &quadVaoId);
    glBindVertexArray(quadVaoId);
    glGenBuffers(1, &quad.vertBuf);
    glBindBuffer(GL_ARRAY_BUFFER, quad.vertBuf);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad.vertices), quad.vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);
    glGenBuffers(1, &quad.colorBuf);
    glBindBuffer(GL_ARRAY_BUFFER, quad.colorBuf);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad.colors), quad.colors, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);
    glGenBuffers(1, &quad.uvBuf);
    glBindBuffer(GL_ARRAY_BUFFER, quad.uvBuf);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad.uvs), quad.uvs, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(2);
    
    GLuint modelMatLocation = glGetUniformLocation(program, "modelMat");
    GLuint viewMatLocation = glGetUniformLocation(program, "viewMat");
    GLuint projMatLocation = glGetUniformLocation(program, "projMat");
    
    tfw::Scene scene;
    
    ygl::image4b im = ygl::make_grid_image(256, 256);
    GLuint tex;
    glGenTextures(1, &tex);
    //glBindTexture(GL_TEXTURE_2D, tex);
    float pixels[] = {
        1.0f, 1.0f, 1.0f,   0.f, 0.f, 0.f, 0.f,
        0.f, 0.f, 0.f, 0.f,   1.0f, 1.0f, 1.0f
    };
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256, 256, 0, GL_RGBA, GL_UNSIGNED_BYTE, im.data());
    glUniform1i(glGetUniformLocation(program, "tex"), 0);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    while (!glfwWindowShouldClose(window))
    {
        float ratio;
        int width, height;
        mat4x4 m, v, p;
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_DEPTH_BUFFER_BIT);
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

        glBindVertexArray(quadVaoId);
        glDrawArrays(GL_TRIANGLES, 0, 6);
                    glBindVertexArray(triVaoId);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        
        
        scene.render();
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}