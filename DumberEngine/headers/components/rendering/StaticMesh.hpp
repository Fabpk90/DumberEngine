//
// Created by fab on 20/11/2020.
//

#ifndef DUMBERENGINE_STATICMESH_HPP
#define DUMBERENGINE_STATICMESH_HPP

#include "../IComponent.hpp"
#include "Mesh.hpp"
#include "../../utils/IDragNDrop.hpp"

#include <assimp/scene.h>
#include <vector>

class StaticMesh : public IComponent, public IDragNDrop
{
public:
    void start() override;

    void loadFrom(const char* path);

    void draw() override;

    void drawInspector() override;

    ~StaticMesh() override;

    void OnFileDropped(const char *path) override;

    bool castShadow() override;

    void drawShadow(Shader *pShader) override;

    void fillGBuffer(Shader &shader) override;

    Mesh& getMesh(int index) { return *meshes[index]; }

private:
    void recursivelyLoadNode(aiNode *const pNode, const aiScene *pScene);

    Mesh* loadMeshFrom(aiMesh& mesh, const aiScene* scene);
    std::vector<Texture2D*> loadMaterialTexturesType(aiMaterial *pMaterial, aiTextureType type);

private:
    //TODO: fix this, make it not a vector of pointers
    std::vector<Mesh*> meshes;
    std::string path;
    Shader* shader;
    int indexTextureType = 0;
};

#endif //DUMBERENGINE_STATICMESH_HPP
