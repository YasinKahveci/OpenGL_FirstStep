#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP
#include <string>
#include <map>
class ShaderProgram
{
    public:
        ShaderProgram();
        ~ShaderProgram();
        void attachShader(const char* fileName,unsigned int shaderType);
        
        void link();

        void use();

        void addUniform(const std::string& varName);

        void setFloat(const std::string& varNamem,float value);

    private:
        unsigned int m_ProgramId;
        std::map<std::string,unsigned int> m_UniformVars;
        std::string getShaderFromFile(const char* fileName);
        
        
};

#endif