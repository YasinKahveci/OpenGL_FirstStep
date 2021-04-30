#ifndef MESHMANAGER_HPP
#define MESHMANAGER_HPP
#include <Map>
#include <string>
class Mesh;
class VertexArrayObject;
class MeshManager
{
private:
    MeshManager();
    static MeshManager* Point;
    std::map<std::string,VertexArrayObject*> m_VaoMap;
public:
    static MeshManager* getInstance();
    Mesh* CreateCube();
    Mesh* CreateSquare();
};


#endif