#include<iostream>
#include <thread>         
#include <chrono>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include "shaderprogram.hpp"
#include "square.hpp"
#include <vector>
#include <cmath>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
unsigned int programID; 

std::vector<glm::vec3> vertices;
unsigned int VBO;
unsigned int VAO;

void buildCircle(float radius,int vertexCount)
{
    float angle=360.0f/vertexCount;
    int triangleCount=vertexCount-2;

    std::vector<glm::vec3> tempVertices;
    for (int i = 0; i < vertexCount; i++)
    {
        float newAngle=angle*i;
        float x=radius*cos(glm::radians(newAngle));
        float y=radius*sin(glm::radians(newAngle));
        float z=0.0f;
        tempVertices.push_back(glm::vec3(x,y,z));
    }
    for (int i = 0; i < triangleCount; i++)
    {
        vertices.push_back(tempVertices[0]);
        vertices.push_back(tempVertices[i+1]);
        vertices.push_back(tempVertices[i+2]);
    }
}

int main(int argc,char** argv)
{
    if(!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window= glfwCreateWindow(800,800,"Ilk Programim",NULL,NULL);
    if (window==NULL)
    {
        std::cout<<"Pencere Olusturulamadi"<<std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout <<"Failed  to initialize GLAD "<<std::endl;
    }

    buildCircle(0.5,72);
    ShaderProgram program;

    program.attachShader("./shaders/simplevs.glsl",GL_VERTEX_SHADER);
    program.attachShader("./shaders/simplefs.glsl",GL_FRAGMENT_SHADER);
    program.link();

    program.addUniform("uMove");
    program.addUniform("uColor");
    //vertex buffer object

    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(glm::vec3)*vertices.size(),&vertices[0],GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(float)*3,(void*)0);
    
    glEnableVertexAttribArray(0);
    

    while(!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f,0.4f,0.7f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        program.use();
        glBindVertexArray(VAO);
        program.setvec3("uMove",glm::vec3(0.0f,0.0f,0.0f));
        program.setvec4("uColor",glm::vec4(1.0f,0.0f,0.0f,1.0f));
        glDrawArrays(GL_TRIANGLES,0,vertices.size());



        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
}