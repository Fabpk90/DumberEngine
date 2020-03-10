//
// Created by ELE5d5b9c842bce2 on 10/03/2020.
//

#ifndef DUMBERENGINE_ISYSTEM_HPP
#define DUMBERENGINE_ISYSTEM_HPP

class ISystem
{
public:

    virtual ~ISystem() = default;

    virtual void init() = 0;
    virtual void update() = 0;
};

#endif //DUMBERENGINE_ISYSTEM_HPP
