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
#include "vertexarrayobject.hpp"
#include "Mesh.hpp"
#include "MeshManager.hpp"
unsigned int programID; 



float aci=0.0f;
float scale=1.0f;
glm::vec3 position=glm::vec3(0.0f,0.0f,0.0f);
unsigned int Texture;
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
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

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

    
    MeshManager* manager=MeshManager::getInstance();
    Mesh* mesh=manager->CreateCube();

    Texture=TextureManager::getInstance()->loadTexture("./images/brick.jpg");

    ShaderProgram program;
    program.attachShader("./shaders/simplevs.glsl",GL_VERTEX_SHADER);
    program.attachShader("./shaders/simplefs.glsl",GL_FRAGMENT_SHADER);
    program.link();

    program.addUniform("uColor");
    program.addUniform("uMtxTransform");
    
    glm::mat4 mtxProj=glm::perspective(glm::radians(90.0f),800.0f/800.0f,1.0f,100.0f);
    
    glm::vec3 camPosition(4.0f,-1.0f,5.0f);
    glm::vec3 camLookAt(0.0f,0.0f,0.0f);
    glm::vec3 camUp(0.0f,1.0f,0.0f);

    glm::mat4 mtxCam=glm::lookAt(camPosition,camLookAt,camUp);
    glm::mat4 mtxTransform(1);
    glEnable(GL_DEPTH_TEST);
    
    while(!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f,0.4f,0.7f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        program.use();
        TextureManager::getInstance()->activateTexture(GL_TEXTURE0,Texture);
        glm::mat3 mtxRotation=glm::rotate(glm::mat3(1),glm::radians(0.0f));  
        glm::mat4 mtxTranslation = glm::translate(glm::mat4(1),position);
        glm::mat3 mtxScale=glm::scale(glm::mat3(1),glm::vec2(scale,scale));
        mtxTransform=mtxProj*mtxCam*mtxTranslation*(glm::mat4(mtxRotation))*(glm::mat4(mtxScale));

        program.setvec4("uColor",glm::vec4(1.0f,0.0f,0.0f,1.0f));
        program.setMat4("uMtxTransform",&mtxTransform);  
        
        mesh->Draw();

        TextureManager::getInstance()->activateTexture(GL_TEXTURE0,Texture);
        mtxRotation=glm::rotate(glm::mat3(1),glm::radians(0.0f));  
        mtxTranslation = glm::translate(glm::mat4(1),position+glm::vec3(1.0f,0.0f,0.0f));
        mtxScale=glm::scale(glm::mat3(1),glm::vec2(scale,scale));
        mtxTransform=mtxProj*mtxCam*mtxTranslation*(glm::mat4(mtxRotation))*(glm::mat4(mtxScale));

        program.setvec4("uColor",glm::vec4(1.0f,0.0f,0.0f,1.0f));
        program.setMat4("uMtxTransform",&mtxTransform);  
        mesh->Draw();

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
}