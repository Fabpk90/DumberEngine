//
// Created by fab on 20/11/2020.
//

#include <fstream>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <iostream>
#include "../../../headers/components/IComponent.hpp"
#include "../../../headers/components/rendering/StaticMesh.hpp"
#include "../../../headers/rendering/renderer/Camera.hpp"
#include "../../../headers/systems/Editor.hpp"

void StaticMesh::draw()
{
    shader->use();

    shader->setMatrix4("m", transform->getModelMatrix());
    glm::mat4 v = Camera::getInstance().getViewMatrix();
    shader->setMatrix4("v", v);
    auto p = Camera::getInstance().getProjectionMatrix();
    shader->setMatrix4("p", p);

    auto pos = glm::vec3(2, 2, 2);
    shader->setVec3("lightPos", pos);
    auto color = glm::vec3(0, 1, 0);
    shader->setVec3("lightColor", color);

    shader->setVec3("cameraPos", Camera::getInstance().position);

    for(const auto mesh : meshes)
    {
        mesh->draw(shader);
    }
}


void StaticMesh::loadFrom(const char *path)
{
    this->path = path;
    auto index = this->path.find_last_of('/') + 1; // +1 to include the /
    this->path = this->path.substr(0, index);
    //TODO: add an assetloader to map stuff already loaded

    std::ifstream file(path);

    if(!file.bad())
    {
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);

        meshes.reserve(scene->mNumMeshes);

        recursivelyLoadNode(scene->mRootNode, scene);

        importer.FreeScene();
    }
}

void StaticMesh::recursivelyLoadNode(aiNode *const pNode, const aiScene *pScene)
{
    for(int i = 0; i < pNode->mNumMeshes; i++)
    {
        meshes.emplace_back(loadMeshFrom(*pScene->mMeshes[pNode->mMeshes[i]], pScene));
    }

    for(int i = 0; i < pNode->mNumChildren; i++)
    {
        recursivelyLoadNode(pNode->mChildren[i], pScene);
    }
}

Mesh* StaticMesh::loadMeshFrom(aiMesh &mesh, const aiScene *scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture2D*> textures;

    vertices.reserve(mesh.mNumVertices);
    indices.reserve(mesh.mNumFaces);


    for(int i = 0; i < mesh.mNumVertices; i++)
    {
        Vertex v{};

        v.Position.x = mesh.mVertices[i].x;
        v.Position.y = mesh.mVertices[i].y;
        v.Position.z = mesh.mVertices[i].z;

        v.Normal.x = mesh.mNormals[i].x;
        v.Normal.y = mesh.mNormals[i].y;
        v.Normal.z = mesh.mNormals[i].z;

        v.TexCoords.x = mesh.mTextureCoords[0][i].x;
        v.TexCoords.y = mesh.mTextureCoords[0][i].y;

        vertices.emplace_back(v);
    }

    for(int i = 0; i < mesh.mNumFaces; i++)
    {
        auto face = mesh.mFaces[i];

        for(int j = 0; j < face.mNumIndices; j++)
        {
            indices.emplace_back(face.mIndices[j]);
        }
    }

    //the mesh has some materials
    if(mesh.mMaterialIndex >= 0)
    {
        auto mat = scene->mMaterials[mesh.mMaterialIndex];

        auto texAlbedo = loadMaterialTexturesType(mat, aiTextureType_BASE_COLOR);

        aiString texture_file;
        if(mat->Get(AI_MATKEY_TEXTURE(aiTextureType_DIFFUSE, 0), texture_file) == aiReturn_SUCCESS)
        {

        }

        auto texHas = scene->HasTextures();

        if(texHas)
            std::cout << "yes" << std::endl;

        auto tex = scene->GetEmbeddedTexture(texture_file.C_Str());
        if(tex)
        {

        }

        if(texAlbedo.empty())
            texAlbedo = loadMaterialTexturesType(mat, aiTextureType_DIFFUSE);

        textures = texAlbedo;

        auto texSpecular = loadMaterialTexturesType(mat, aiTextureType_SPECULAR);

        if(texSpecular.empty())
        {
            texSpecular = loadMaterialTexturesType(mat, aiTextureType_HEIGHT);
        }

        auto texMetallic = loadMaterialTexturesType(mat, aiTextureType_METALNESS);
        auto texRoughness = loadMaterialTexturesType(mat, aiTextureType_DIFFUSE_ROUGHNESS);
        auto texAO = loadMaterialTexturesType(mat, aiTextureType_AMBIENT_OCCLUSION);

        textures.insert(textures.end(), texSpecular.begin(), texSpecular.end());
        textures.insert(textures.end(), texMetallic.begin(), texMetallic.end());
        textures.insert(textures.end(), texRoughness.begin(), texRoughness.end());
        textures.insert(textures.end(), texAO.begin(), texAO.end());
    }

    return new Mesh(vertices, indices, textures);
}

std::vector<Texture2D*> StaticMesh::loadMaterialTexturesType(aiMaterial *pMaterial, aiTextureType type)
{
    std::vector<Texture2D*> tex;

    tex.resize(pMaterial->GetTextureCount(type));

    for(int i = 0; i < pMaterial->GetTextureCount(type); i++)
    {
        aiString texturePath;

        if(pMaterial->GetTexture(type, i, &texturePath) == aiReturn_SUCCESS)
        {
            std::string texPath(path);
            texPath.append(texturePath.C_Str());

            tex[i] = new Texture2D();
            tex[i]->loadFrom(texPath.c_str(), ITexture::convertFrom(type));
        }
    }

    return tex;
}

void StaticMesh::start()
{
    Editor::instance->addDragNDropCallback(this);
    shader = new Shader("shaders/forward/pbr/");

    transform->setPosition(0, 0, 0);
}

StaticMesh::~StaticMesh()
{
    delete shader;

    for(auto mesh : meshes)
        delete mesh;

    if(Editor::instance)
        Editor::instance->addDragNDropCallback(this);
}

void StaticMesh::drawInspector()
{
    ImGui::Text("Textures from Mesh");

    static char buf[1024];
    ImGui::InputText("Texturepath", buf, 1024);

    static char* items[] = {"Albedo","Normal","Metalness","AO","Roughness"};
    ImGui::Combo("Texture type", &indexTextureType, items, 5);
    if(ImGui::Button("Load Texture"))
    {
    //TODO: drag and drop to add textures
        Texture2D* tex = new Texture2D();
        tex->loadFrom(buf, static_cast<ITexture::ETextureType>(ITexture::Albedo + indexTextureType));
        std::cout << "size before " << meshes[0]->getTextures().size() << std::endl;
        meshes[0]->getTextures().push_back(tex);
        std::cout << "size after " << meshes[0]->getTextures().size() << std::endl;
    }

    Texture2D* texToDelete = nullptr;
    Mesh* textureOwner = nullptr;
    for(auto& mesh : meshes)
    {
       for(auto tex : mesh->getTextures())
       {
           ImGui::PushID(tex);
           if(ImGui::Button("X"))
           {
               texToDelete = tex;
               textureOwner = mesh;
           }
           ImGui::Image((void*)(intptr_t) tex->getID(), ImVec2(256, 256));
           ImGui::PopID();
       }
    }

    if(texToDelete)
    {
        auto& textures = textureOwner->getTextures();
        auto index = std::find(textures.begin(), textures.end(), texToDelete);
        textureOwner->getTextures().erase(index);

        delete texToDelete;
    }
}

void StaticMesh::OnFileDropped(const char *filePath)
{
    Texture2D* tex = new Texture2D();
    if(!tex->loadFrom(filePath, static_cast<ITexture::ETextureType>(ITexture::Albedo + indexTextureType)))
    {
        delete tex;
    }
    else
        meshes[0]->getTextures().push_back(tex);
}

bool StaticMesh::castShadow()
{
    return true;
}

void StaticMesh::drawShadow(Shader *pShader)
{
    IComponent::drawShadow(pShader);

    pShader->use();
    pShader->setMatrix4("model", transform->getModelMatrix());

    for(auto* mesh : meshes)
    {
        mesh->drawShadows();
    }
}

void StaticMesh::fillGBuffer(Shader &shader)
{
    shader.use();

    shader.setMatrix4("m", transform->getModelMatrix());
    glm::mat4 v = Camera::getInstance().getViewMatrix();
    shader.setMatrix4("v", v);
    auto p = Camera::getInstance().getProjectionMatrix();
    shader.setMatrix4("p", p);

    for(const auto& mesh : meshes)
    {
        mesh->draw(&shader);
    }
}
