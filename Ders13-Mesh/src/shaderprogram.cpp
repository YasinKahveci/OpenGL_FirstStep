#include"shaderprogram.hpp"
#include<glad/glad.h>
#include<fstream>
#include<iostream>
ShaderProgram::ShaderProgram()
{
    m_ProgramId=glCreateProgram();
}
ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(m_ProgramId);
}
void ShaderProgram::link()
{
    glLinkProgram(m_ProgramId);
    int isLinked;
    char log[512];
    glGetProgramiv(m_ProgramId,GL_LINK_STATUS,&isLinked);

    if (!isLinked)
    {
        glGetProgramInfoLog(m_ProgramId,512,0,log);
        std::cout<<"Linking Error "<<log<<std::endl;
    }
}
void ShaderProgram::use()
{
    glUseProgram(m_ProgramId);
}
void ShaderProgram::attachShader(const char* fileName,unsigned int shaderType) 
{
    unsigned int shaderID=glCreateShader(shaderType);

    std::string sourceCode=getShaderFromFile(fileName);

    const char* chSourceCode=&sourceCode[0];

    glShaderSource(shaderID,1,&chSourceCode,0);

    glCompileShader(shaderID);

    int isComplied;
    char log[512];
    glGetShaderiv(shaderID,GL_COMPILE_STATUS,&isComplied);
    if (!isComplied)
    {
        glGetShaderInfoLog(shaderID,512,0,log);
        std::cout<<"Error Shader Type: "<<shaderType<<std::endl<<log<<std::endl;
    }
    

    glAttachShader(m_ProgramId,shaderID);

    glDeleteShader(shaderID);

}

void ShaderProgram::addUniform(const std::string& varName)
{
    m_UniformVars[varName]=glGetUniformLocation(m_ProgramId,varName.c_str());
}

void ShaderProgram::setFloat(const std::string& varName,float value)
{
    glUniform1f(m_UniformVars[varName],value);
}
void ShaderProgram::setvec3(const std::string& varName,const glm::vec3& value)
{
    glUniform3f(m_UniformVars[varName],value.x,value.y,value.z);
}
void ShaderProgram::setvec4(const std::string& varName,const glm::vec4& value)
{
    glUniform4f(m_UniformVars[varName],value.r,value.g,value.b,value.a);
}
void ShaderProgram::setMat3(const std::string& varName,const glm::mat3* ptrValue)
{
    glUniformMatrix3fv(m_UniformVars[varName],1,false,(GLfloat*)ptrValue);
}
std::string ShaderProgram::getShaderFromFile(const char* fileName)
{
    std::ifstream file(fileName);

    std::string data;

    if (file.is_open())
    {
        char readChar;
        
        while ((readChar=file.get())!=EOF)
        {
            data+=readChar;
        }
        file.close();
    }
    return data;
}
void ShaderProgram::setMat4(const std::string& varName,const glm::mat4* mtx)
{
    glUniformMatrix4fv(m_UniformVars[varName],1,false,(GLfloat*)mtx);
}