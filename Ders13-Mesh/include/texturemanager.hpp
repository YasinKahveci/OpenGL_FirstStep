#ifndef TextureManager_HPP
#define TextureManager_HPP
#include <string>
#include <map>
class TextureManager
{
public:
    static TextureManager* getInstance();
    unsigned int loadTexture(std::string fileName);
    void activateTexture(unsigned int level,unsigned int id);
private:
    TextureManager();
    static TextureManager* m_Instance;
    std::map <std::string,unsigned int>  m_TextureMap;
};


#endif