#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include "shaderprogram.hpp"
unsigned int programID; 

float vertices[]={
    -0.6f,-0.6f,0.0f,
    0.6f,-0.6f,0.0f,
    0.0f,0.6f,0.0f,
    0.0f,0.6f,0.0f,
    -0.8f,0.9f,0.0f,
    0.8f,0.9f,0.0f,
};
unsigned int VBO;
unsigned int VAO;

float deger=0.0f;
void key_callback(GLFWwindow* window,int key,int scancode,int action,int mods)
{
    if(key==GLFW_KEY_ESCAPE)
        glfwTerminate();
    if (key==GLFW_KEY_LEFT)
    {
        deger-=0.01;
    }
    if (key==GLFW_KEY_RIGHT)
    {
        deger+=0.01;
    }
    
}

int main(int argc,char** argv)
{
    if(!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window= glfwCreateWindow(800,600,"Ilk Programim",NULL,NULL);
    if (window==NULL)
    {
        std::cout<<"Pencere Olusturulamadi"<<std::endl;
        glfwTerminate();
        return -1;
    }
    glfwSetKeyCallback(window,key_callback);
    glfwMakeContextCurrent(window);
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout <<"Failed  to initialize GLAD "<<std::endl;
    }


    ShaderProgram program;

    program.attachShader("./shaders/simplevs.glsl",GL_VERTEX_SHADER);
    program.attachShader("./shaders/simplefs.glsl",GL_FRAGMENT_SHADER);
    program.link();

    program.addUniform("uMoveX");
    //vertex buffer object

    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(float)*3,(void*)0);
    
    glEnableVertexAttribArray(0);
    

    while(!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f,0.4f,0.7f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        program.use();
        program.setFloat("uMoveX",deger);
        glBindVertexArray(VAO);

        glDrawArrays(GL_TRIANGLES,0,6);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
}