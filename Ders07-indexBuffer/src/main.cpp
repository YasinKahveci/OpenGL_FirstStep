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
#include <glm/gtx/matrix_transform_2d.hpp>
#include <stb_image.h>
unsigned int programID; 



std::vector<glm::vec3> vertices;
std::vector<unsigned int> indices;

float aci=0.0f;
float scale;
glm::vec2 position;
float r_radius=0.2f;
unsigned int VBO;
unsigned int VAO;
unsigned int EBO;
void buildCircle(float radius,int detailValue)
{
    if(detailValue<=0)
            detailValue = 1;

    int vertexCount = 4*detailValue;
    int triCount    = vertexCount-2;
    float angle     = 360.0f/vertexCount;

    for(int i=0;i<vertexCount;i++)
    {
        glm::vec3 nextPos;
        float nextAngle = angle*i;
        nextPos.x = radius*glm::cos(glm::radians(nextAngle));
        nextPos.y = radius*glm::sin(glm::radians(nextAngle));
        nextPos.z = 1.0f;
        vertices.push_back(nextPos);
    }
    for(int i =0;i<triCount;i++)
    {
        int index = i;

        indices.push_back(0);
        indices.push_back(index+1);
        indices.push_back(index+2);
        
    }
}
void key_callback(GLFWwindow* window,int key,int scancode,int action,int mods)
{
    if(key==GLFW_KEY_ESCAPE)
        glfwTerminate();
    if (action==GLFW_PRESS)
    {
        if (key==GLFW_KEY_LEFT)
        {
            position.x-=r_radius;
        }
        if (key==GLFW_KEY_RIGHT)
        {
            position.x+=r_radius;
        }
        if (key==GLFW_KEY_UP)
        {
            position.y+=r_radius;
        }
        if (key==GLFW_KEY_DOWN)
        {
            position.y-=r_radius;
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

    buildCircle(r_radius,2);
    aci=0.0f;
    scale=1.0f;
    position=glm::vec2(0.0f,0.0f);
    glm::mat3 mtxTransform(1);
    


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
    glBufferData(GL_ARRAY_BUFFER,sizeof(glm::vec3)*vertices.size(),&vertices[0],GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(float)*3,(void*)0);
    
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(unsigned int)*indices.size(),&indices[0],GL_STATIC_DRAW);

    while(!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f,0.4f,0.7f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        program.use();
        
        glm::mat3 mtxRotation=glm::rotate(glm::mat3(1),glm::radians(aci));  
        glm::mat3 mtxTranslation = glm::translate(glm::mat3(1),position);
        glm::mat3 mtxScale=glm::scale(glm::mat3(1),glm::vec2(scale,scale));
        mtxTransform=mtxTranslation*mtxRotation*mtxScale;
        aci+=1.0f;
        glBindVertexArray(VAO);
        program.setvec4("uColor",glm::vec4(1.0f,0.0f,0.0f,1.0f));
        program.setMat3("uMtxTransform",&mtxTransform);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        

        std::this_thread::sleep_for(std::chrono::milliseconds(70));
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
}