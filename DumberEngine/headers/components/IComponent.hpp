//
// Created by fab on 25/02/2020.
//

#ifndef DUMBERENGINE_ICOMPONENT_HPP
#define DUMBERENGINE_ICOMPONENT_HPP

class IComponent
{
public:
    virtual void start() = 0;

    virtual void update() = 0;

    virtual void draw() = 0;

    //used to show params in the inspector
    virtual void drawInspector() = 0;

    virtual ~IComponent()
    {};

public:
    unsigned int gameObjectIndex;
};

#endif //DUMBERENGINE_ICOMPONENT_HPP
