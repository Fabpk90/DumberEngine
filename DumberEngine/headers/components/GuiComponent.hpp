//
// Created by fab on 09/04/2020.
//

#ifndef DUMBERENGINE_GUICOMPONENT_HPP
#define DUMBERENGINE_GUICOMPONENT_HPP

class GuiComponent
{
protected:
    bool isActive;
public:
    //used to show params in the inspector
    virtual void drawInspector() = 0;

    virtual ~GuiComponent()= default;
};

#endif //DUMBERENGINE_GUICOMPONENT_HPP
