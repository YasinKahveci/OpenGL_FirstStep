#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

unsigned int programID;

//vertex shader
char* vsSource=
"#version 330 core\n                          \
layout (location = 0) in vec3 inPosition;     \
void main()                                   \
{                                             \
    gl_Position = vec4(inPosition,1.0);       \
}";
//fragment shader
char* fsSource=
"#version 330 core\n                          \
out vec4 fragColor;                           \
void main()                                   \
{                                             \
    fragColor = vec4(1.0f,0.0f,0.0f,1.0f);    \
}";

float vertices[]={
    -0.6f,-0.6f,0.0f,
    0.5f,-0.5f,0.0f,
    0.0f,0.5f,0.0f
};

int main()
{
    if(!glfwInit())
        return -1;
    GLFWwindow* window= glfwCreateWindow(800,600,"Ilk Programim",NULL,NULL);
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


    programID=glCreateProgram();

    unsigned int vertexShaderId=glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShaderId,1,&vsSource,NULL);

    glCompileShader(vertexShaderId);


    unsigned int fragmentShaderId=glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragmentShaderId,1,&fsSource,NULL);

    glCompileShader(fragmentShaderId);

    glAttachShader(programID,vertexShaderId);

    glAttachShader(programID,fragmentShaderId);

    glLinkProgram(programID);

    //vertex buffer object
    unsigned int VBO;
    unsigned int VAO;
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(float)*3,(void*)0);
    
    glEnableVertexAttribArray(0);
    

    while(!glfwWindowShouldClose(window))
    {
        glClearColor(1.0f,1.0f,1.0f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(programID);

        glBindVertexArray(VAO);
        glEnableVertexAttribArray(0);

        glDrawArrays(GL_TRIANGLES,0,3);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
}