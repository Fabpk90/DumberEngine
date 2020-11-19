//
// Created by fab on 20/11/2020.
//

#ifndef DUMBERENGINE_STATICMESH_HPP
#define DUMBERENGINE_STATICMESH_HPP

#include "../IComponent.hpp"
#include "Mesh.hpp"

#include <assimp/scene.h>
#include <vector>

class StaticMesh : public IComponent
{
public:
    void loadFrom(const char* path);

    void draw() override;

private:
    void recursivelyLoadNode(aiNode *const pNode, const aiScene *pScene);

    Mesh* loadMeshFrom(aiMesh& mesh, const aiScene* scene);

private:
    std::vector<Mesh*> meshes;
};

#endif //DUMBERENGINE_STATICMESH_HPP
