// Two-Dimensional Sierpinski Gasket
// Generated using randomly selected vertices and bisection

#include "Angel.h"

// https://stackoverflow.com/questions/22118518/use-of-undeclared-identifier-glgenvertexarrays-error-even-after-including-open
#ifdef __APPLE__

#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>

#endif

const int NumPoints = 5000;

GLFWwindow *window = NULL;

//----------------------------------------------------------------------------

void init(void)
{
    vec2 points[NumPoints];

    // Specifiy the vertices for a triangle
    vec2 vertices[3] = {
        vec2(-1.0, -1.0), vec2(0.0, 1.0), vec2(1.0, -1.0)};

    // Select an arbitrary initial point inside of the triangle
    points[0] = vec2(0.25, 0.50);

    // compute and store N-1 new points
    for (int i = 1; i < NumPoints; ++i)
    {
        int j = rand() % 3; // pick a vertex at random

        // Compute the point halfway between the selected vertex
        //   and the previous point
        points[i] = (points[i - 1] + vertices[j]) / 2.0;
    }

    // Create a vertex array object
    GLuint vao[1];
    glGenVertexArrays(1, vao);
    glBindVertexArray(vao[0]);

    // Create and initialize a buffer object
    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

    // Load shaders and use the resulting shader program
    GLuint program = InitShader("vshader21.glsl", "fshader21.glsl");
    glUseProgram(program);

    // Initialize the vertex position attribute from the vertex shader
    GLuint loc = glGetAttribLocation(program, "vPosition");
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

    glClearColor(.0, .0, .0, 1.0); // black background
}

//----------------------------------------------------------------------------

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);          // clear the window
    glDrawArrays(GL_POINTS, 0, NumPoints); // draw the points

    glfwSwapBuffers(window);
    glfwPollEvents();
}

//----------------------------------------------------------------------------

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 033:
        exit(EXIT_SUCCESS);
        break;
    }
}

//----------------------------------------------------------------------------

int main(int argc, char **argv)
{

    // Initialise GLFW
    glfwInit();

    // Open a window and create its OpenGL context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(800, 600, "Example1 - Window", NULL, NULL);

    glfwMakeContextCurrent(window);

    init();

    do
    {
        display();
    } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(window));

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    exit(EXIT_SUCCESS);
}
