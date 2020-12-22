//
// Created by fab on 25/02/2020.
//

#ifndef DUMBERENGINE_SCENE_HPP
#define DUMBERENGINE_SCENE_HPP

#include <unordered_map>
#include "../components/GameObject.hpp"
#include "helper/Shader.hpp"
#include "../components/rendering/IPostRendering.hpp"

#include <memory>

class Scene
{
private:
    std::unordered_map<unsigned int, std::shared_ptr<GameObject>> gameObjects;
    unsigned int indexCounter;

    std::vector<GameObject*> toStart;

    GameObject* selectedGO;

    std::string name;

public:
    static Scene* instance;

public:
    Scene();

    void update();

    void draw();
    void drawPostRendering();
    void drawCastingShadowObjects(Shader *pShader);

    void removeGameObject(std::string name);

    void drawInspector();

    std::shared_ptr<GameObject> getGameObject(unsigned int index);

    void save();

    std::shared_ptr<GameObject> createGameObject(const char *string);
};

#endif //DUMBERENGINE_SCENE_HPP
