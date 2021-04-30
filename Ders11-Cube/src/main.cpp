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
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>
#include "texturemanager.hpp"
unsigned int programID; 


struct Vertex
{
    glm::vec3 pos;
    glm::vec4 color;
};

std::vector<Vertex> vertices;
std::vector<unsigned int> indices;

float aci=0.0f;
float scale=1.0f;
glm::vec3 position;
float r_radius=1.0f;
unsigned int VBO;
unsigned int VAO;
unsigned int EBO;
unsigned int Texture;
void buildSquare(float length)
{
    Vertex v0,v1,v2,v3,v4,v5,v6,v7;
    v0.pos = glm::vec3(-length/2,-length/2,-length/2);
    v1.pos = glm::vec3(length/2,-length/2,-length/2);
    v2.pos = glm::vec3(length/2,-length/2,length/2);
    v3.pos = glm::vec3(-length/2,-length/2,length/2);

    v4.pos = glm::vec3(-length/2,length/2,-length/2);
    v5.pos = glm::vec3(length/2,length/2,-length/2);
    v6.pos = glm::vec3(length/2,length/2,length/2);
    v7.pos = glm::vec3(-length/2,length/2,length/2);

    v0.color = glm::vec4(1.0f,0.0f,0.0f,1.0f);
    v1.color = glm::vec4(1.0f,1.0f,0.0f,1.0f);
    v2.color = glm::vec4(1.0f,0.0f,1.0f,1.0f);
    v3.color = glm::vec4(0.0f,1.0f,0.0f,1.0f);

    v4.color = glm::vec4(1.0f,0.0f,1.0f,1.0f);
    v5.color = glm::vec4(0.0f,1.0f,1.0f,1.0f);
    v6.color = glm::vec4(0.0f,0.0f,1.0f,1.0f);
    v7.color = glm::vec4(1.0f,1.0f,0.0f,1.0f);

    vertices.push_back(v0);
    vertices.push_back(v1);
    vertices.push_back(v2);
    vertices.push_back(v3);
    vertices.push_back(v4);
    vertices.push_back(v5);
    vertices.push_back(v6);
    vertices.push_back(v7);

    //on yuz
    indices.push_back(7);
    indices.push_back(3);
    indices.push_back(2);
    
    indices.push_back(7);
    indices.push_back(2);
    indices.push_back(6);
    //arka yuz
    indices.push_back(6);
    indices.push_back(2);
    indices.push_back(1);
    
    indices.push_back(6);
    indices.push_back(1);
    indices.push_back(5);

    //ust yuz
    indices.push_back(4);
    indices.push_back(7);
    indices.push_back(6);
    
    indices.push_back(4);
    indices.push_back(6);
    indices.push_back(5);    

    //alt yuz
    indices.push_back(0);
    indices.push_back(3);
    indices.push_back(2);
    
    indices.push_back(0);
    indices.push_back(2);
    indices.push_back(1);    



    //arka  yuz
    indices.push_back(4);
    indices.push_back(0);
    indices.push_back(1);
    
    indices.push_back(4);
    indices.push_back(1);
    indices.push_back(5);  

    
    //sol yuz
    indices.push_back(7);
    indices.push_back(3);
    indices.push_back(0);
    
    indices.push_back(7);
    indices.push_back(0);
    indices.push_back(4);  
}

void key_callback(GLFWwindow* window,int key,int scancode,int action,int mods)
{
    if(key==GLFW_KEY_ESCAPE)
        glfwTerminate();
    if (action==GLFW_PRESS)
    {
        if (key==GLFW_KEY_LEFT)
        {
            position.x-=scale;
        }
        if (key==GLFW_KEY_RIGHT)
        {
            position.x+=scale;
        }
        if (key==GLFW_KEY_UP)
        {
            position.y+=scale;
        }
        if (key==GLFW_KEY_DOWN)
        {
            position.y-=scale;
        }
        if (key==GLFW_KEY_E)
        {
            position.z+=scale;
        }
        if (key==GLFW_KEY_D)
        {
            position.z-=scale;
        }
        if (key==GLFW_KEY_W)
        {
            scale+=0.1;
        }
        if (key==GLFW_KEY_S)
        {
            scale-=0.1;
        }
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
    glfwSetKeyCallback(window,key_callback);
    glfwMakeContextCurrent(window);
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout <<"Failed  to initialize GLAD "<<std::endl;
    }

    buildSquare(r_radius);

    Texture=TextureManager::getInstance()->loadTexture("./images/container.jpg");

    aci=0.0f;
    position=glm::vec3(0.0f,0.0f,0.0f);
    glm::mat4 mtxTransform(1);
    


    ShaderProgram program;

    program.attachShader("./shaders/simplevs.glsl",GL_VERTEX_SHADER);
    program.attachShader("./shaders/simplefs.glsl",GL_FRAGMENT_SHADER);
    program.link();

    program.addUniform("uColor");
    program.addUniform("uMtxTransform");
    
    //vertex buffer object

    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);

    glGenBuffers(1,&EBO);
    
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(Vertex)*vertices.size(),&vertices[0],GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(float)*7,(void*)0);
    glEnableVertexAttribArray(0);
    //kaplama
    glVertexAttribPointer(1,4,GL_FLOAT,GL_FALSE,sizeof(float)*7,(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(unsigned int)*indices.size(),&indices[0],GL_STATIC_DRAW);


    glm::mat4 mtxProj=glm::perspective(glm::radians(90.0f),800.0f/800.0f,1.0f,100.0f);
    
    glm::vec3 camPosition(0.0f,0.0f,5.0f);
    glm::vec3 camLookAt(0.0f,0.0f,0.0f);
    glm::vec3 camUp(0.0f,1.0f,0.0f);

    glm::mat4 mtxCam=glm::lookAt(camPosition,camLookAt,camUp);

    glEnable(GL_DEPTH_TEST);
    while(!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f,0.4f,0.7f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        program.use();

        glm::mat3 mtxRotation=glm::rotate(glm::mat3(1),glm::radians(aci));  
        glm::mat4 mtxTranslation = glm::translate(glm::mat4(1),position);
        glm::mat3 mtxScale=glm::scale(glm::mat3(1),glm::vec2(scale,scale));
        mtxTransform=mtxProj*mtxCam*mtxTranslation*(glm::mat4(mtxRotation))*(glm::mat4(mtxScale));
        aci+=0.8f;
        glBindVertexArray(VAO);
        program.setvec4("uColor",glm::vec4(1.0f,0.0f,0.0f,1.0f));
        program.setMat4("uMtxTransform",&mtxTransform);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
}