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
#include<cstdlib>
#include "Shape.hpp"
#include "Rules.hpp"
unsigned int programID; 

std::vector<glm::vec3> Duvar;//Ekranin koselerine kaplama yerlestirmek istedim klasik Kareler ile .
Rules* Oyun=Rules::getInstance();
unsigned int Texture;
unsigned int Texture1;
void DuvarTanimla();
void key_callback(GLFWwindow* window,int key,int scancode,int action,int mods)
{
    if(key==GLFW_KEY_ESCAPE)
        glfwTerminate();
    if (action==GLFW_PRESS)
    {
        if (key==GLFW_KEY_LEFT)
        {
            Oyun->Shapes.at(Oyun->Shapes.size()-1).setYon(Shape::Left);
        }
        if (key==GLFW_KEY_RIGHT)
        {
            Oyun->Shapes.at(Oyun->Shapes.size()-1).setYon(Shape::Right);
        }
        if (key==GLFW_KEY_DOWN)
        {
            Oyun->Shapes.at(Oyun->Shapes.size()-1).setYon(Shape::Down);
        }
        if (key==GLFW_KEY_SPACE)
        {
            Oyun->Dondur();
        }
    }
}
void YerCekimi();
int main(int argc,char** argv)
{
    if(!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window= glfwCreateWindow(900,900,"Ilk Programim",NULL,NULL);
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
    Mesh* mesh=manager->CreateSquare();

    Texture=TextureManager::getInstance()->loadTexture("./images/brick.jpg");
    Texture1=TextureManager::getInstance()->loadTexture("./images/waa.jpg");
    ShaderProgram program;
    program.attachShader("./shaders/simplevs.glsl",GL_VERTEX_SHADER);
    program.attachShader("./shaders/simplefs.glsl",GL_FRAGMENT_SHADER);
    program.link();

    program.addUniform("uMtxTransform");
    
    glm::mat4 mtxProj=glm::perspective(glm::radians(90.0f),900.0f/900.0f,1.0f,100.0f);
    
    glm::vec3 camPosition(0.0f,0.0f,5.5f);
    glm::vec3 camLookAt(0.0f,0.0f,0.0f);
    glm::vec3 camUp(0.0f,1.0f,0.0f);

    glm::mat4 mtxCam=glm::lookAt(camPosition,camLookAt,camUp);
    glm::mat4 mtxTransform(1);
    glEnable(GL_DEPTH_TEST);
    DuvarTanimla();
    while(!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f,0.4f,0.7f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        program.use();
        for (int i = 0; i < Duvar.size(); i++)
        {
            TextureManager::getInstance()->activateTexture(GL_TEXTURE0,Texture1);
            glm::mat4 mtxTranslation = glm::translate(glm::mat4(1),Duvar.at(i));
            mtxTransform=mtxProj*mtxCam*mtxTranslation;
            program.setMat4("uMtxTransform",&mtxTransform);
            mesh->Draw();
        }
        
        for (int i = 0; i < Oyun->Shapes.size(); i++)
        {
            for (int j = 0; j<Oyun->Shapes.at(i).Sekil.size(); j++)
            {
                TextureManager::getInstance()->activateTexture(GL_TEXTURE0,Texture);
                glm::mat4 mtxTranslation = glm::translate(glm::mat4(1),Oyun->Shapes.at(i).Sekil.at(j).getPosition());
                mtxTransform=mtxProj*mtxCam*mtxTranslation;
                program.setMat4("uMtxTransform",&mtxTransform);
                mesh->Draw();
            }
        }
        Oyun->OyunDongusu();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
void DuvarTanimla()
{
    Duvar.push_back(glm::vec3(4.5f,4.5f,0.0f));
    Duvar.push_back(glm::vec3(4.5f,4.0f,0.0f));
    Duvar.push_back(glm::vec3(4.5f,3.5f,0.0f));
    Duvar.push_back(glm::vec3(4.5f,3.0f,0.0f));
    Duvar.push_back(glm::vec3(4.5f,2.5f,0.0f));
    Duvar.push_back(glm::vec3(4.5f,2.0f,0.0f));
    Duvar.push_back(glm::vec3(4.5f,1.5f,0.0f));
    Duvar.push_back(glm::vec3(4.5f,1.0f,0.0f));
    Duvar.push_back(glm::vec3(4.5f,0.5f,0.0f));
    Duvar.push_back(glm::vec3(4.5f,0.0f,0.0f));

    Duvar.push_back(glm::vec3(4.5f,-4.5f,0.0f));
    Duvar.push_back(glm::vec3(4.5f,-4.0f,0.0f));
    Duvar.push_back(glm::vec3(4.5f,-3.5f,0.0f));
    Duvar.push_back(glm::vec3(4.5f,-3.0f,0.0f));
    Duvar.push_back(glm::vec3(4.5f,-2.5f,0.0f));
    Duvar.push_back(glm::vec3(4.5f,-2.0f,0.0f));
    Duvar.push_back(glm::vec3(4.5f,-1.5f,0.0f));
    Duvar.push_back(glm::vec3(4.5f,-1.0f,0.0f));
    Duvar.push_back(glm::vec3(4.5f,-0.5f,0.0f));
    Duvar.push_back(glm::vec3(4.5f,-0.0f,0.0f));



    Duvar.push_back(glm::vec3(-4.5f,4.5f,0.0f));
    Duvar.push_back(glm::vec3(-4.5f,4.0f,0.0f));
    Duvar.push_back(glm::vec3(-4.5f,3.5f,0.0f));
    Duvar.push_back(glm::vec3(-4.5f,3.0f,0.0f));
    Duvar.push_back(glm::vec3(-4.5f,2.5f,0.0f));
    Duvar.push_back(glm::vec3(-4.5f,2.0f,0.0f));
    Duvar.push_back(glm::vec3(-4.5f,1.5f,0.0f));
    Duvar.push_back(glm::vec3(-4.5f,1.0f,0.0f));
    Duvar.push_back(glm::vec3(-4.5f,0.5f,0.0f));
    Duvar.push_back(glm::vec3(-4.5f,0.0f,0.0f));

    Duvar.push_back(glm::vec3(-4.5f,-4.5f,0.0f));
    Duvar.push_back(glm::vec3(-4.5f,-4.0f,0.0f));
    Duvar.push_back(glm::vec3(-4.5f,-3.5f,0.0f));
    Duvar.push_back(glm::vec3(-4.5f,-3.0f,0.0f));
    Duvar.push_back(glm::vec3(-4.5f,-2.5f,0.0f));
    Duvar.push_back(glm::vec3(-4.5f,-2.0f,0.0f));
    Duvar.push_back(glm::vec3(-4.5f,-1.5f,0.0f));
    Duvar.push_back(glm::vec3(-4.5f,-1.0f,0.0f));
    Duvar.push_back(glm::vec3(-4.5f,-0.5f,0.0f));

    Duvar.push_back(glm::vec3(-4.0f,4.5f,0.0f));
    Duvar.push_back(glm::vec3(-3.5f,4.5f,0.0f));
    Duvar.push_back(glm::vec3(-3.0f,4.5f,0.0f));
    Duvar.push_back(glm::vec3(-2.5f,4.5f,0.0f));
    Duvar.push_back(glm::vec3(-2.0f,4.5f,0.0f));
    Duvar.push_back(glm::vec3(-1.5f,4.5f,0.0f));
    Duvar.push_back(glm::vec3(-1.0f,4.5f,0.0f));
    Duvar.push_back(glm::vec3(-0.5f,4.5f,0.0f));
    Duvar.push_back(glm::vec3(0.0f,4.5f,0.0f));
    Duvar.push_back(glm::vec3(4.0f,4.5f,0.0f));
    Duvar.push_back(glm::vec3(3.5f,4.5f,0.0f));
    Duvar.push_back(glm::vec3(3.0f,4.5f,0.0f));
    Duvar.push_back(glm::vec3(2.5f,4.5f,0.0f));
    Duvar.push_back(glm::vec3(2.0f,4.5f,0.0f));
    Duvar.push_back(glm::vec3(1.5f,4.5f,0.0f));
    Duvar.push_back(glm::vec3(1.0f,4.5f,0.0f));
    Duvar.push_back(glm::vec3(0.5f,4.5f,0.0f));


    
    Duvar.push_back(glm::vec3(-4.0f,-4.5f,0.0f));
    Duvar.push_back(glm::vec3(-3.5f,-4.5f,0.0f));
    Duvar.push_back(glm::vec3(-3.0f,-4.5f,0.0f));
    Duvar.push_back(glm::vec3(-2.5f,-4.5f,0.0f));
    Duvar.push_back(glm::vec3(-2.0f,-4.5f,0.0f));
    Duvar.push_back(glm::vec3(-1.5f,-4.5f,0.0f));
    Duvar.push_back(glm::vec3(-1.0f,-4.5f,0.0f));
    Duvar.push_back(glm::vec3(-0.5f,-4.5f,0.0f));
    Duvar.push_back(glm::vec3(0.0f,-4.5f,0.0f));
    Duvar.push_back(glm::vec3(4.0f,-4.5f,0.0f));
    Duvar.push_back(glm::vec3(3.5f,-4.5f,0.0f));
    Duvar.push_back(glm::vec3(3.0f,-4.5f,0.0f));
    Duvar.push_back(glm::vec3(2.5f,-4.5f,0.0f));
    Duvar.push_back(glm::vec3(2.0f,-4.5f,0.0f));
    Duvar.push_back(glm::vec3(1.5f,-4.5f,0.0f));
    Duvar.push_back(glm::vec3(1.0f,-4.5f,0.0f));
    Duvar.push_back(glm::vec3(0.5f,-4.5f,0.0f));
}