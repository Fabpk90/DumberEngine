//
// Created by fab on 19/03/2020.
//

#ifndef DUMBERENGINE_IFBO_HPP
#define DUMBERENGINE_IFBO_HPP

#include "IWindow.h"

class IFbo : public ICallbackResize
{
protected:
    int width;
    int height;
    bool hasDepth;
    bool hasColor;
    bool updateOnResize;

public:
    IFbo(int width, int height, bool hasDepth = true, bool hasColor = false, bool updateOnResize = false)
    : width(width), height(height), hasDepth(hasDepth), hasColor(hasColor), updateOnResize(updateOnResize)
    {}

    IFbo(int width, int height, int colorTexId, int depthTexId, bool updateOnResize)
    : width(width), height(height), updateOnResize(updateOnResize)
    {};

    virtual ~IFbo() {};
    virtual void bind() = 0;
    virtual void unBind() = 0;
    virtual void writeToDisk() = 0;
    virtual void enableWrite(bool) = 0;
    virtual void enableRead(bool) = 0;

    void setUpdateOnResize(bool resize) { updateOnResize = resize; }

    int getWidth() { return width;}
    int getHeight() { return height;}

    virtual unsigned int getColorTexture() = 0;
    virtual void setColorTexture(unsigned int id) = 0;

    virtual unsigned int getDepthTexture() = 0;
    virtual void setDepthTexture(unsigned int id) = 0;

    static IFbo* shadowFBO;
};

#endif //DUMBERENGINE_IFBO_HPP
