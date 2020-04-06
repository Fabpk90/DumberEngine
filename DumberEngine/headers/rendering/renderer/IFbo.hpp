//
// Created by fab on 19/03/2020.
//

#ifndef DUMBERENGINE_IFBO_HPP
#define DUMBERENGINE_IFBO_HPP

class IFbo
{
protected:
    int width;
    int height;
    bool hasDepth;
    bool hasColor;

public:
    IFbo(int width, int height, bool hasDepth = true, bool hasColor = false)
    : width(width), height(height), hasDepth(hasDepth), hasColor(hasColor)
    {}

    virtual ~IFbo() {};
    virtual void bind() = 0;
    virtual void unBind() = 0;
    virtual void writeToDisk() = 0;
    virtual void enableWrite(bool) = 0;
    virtual void enableRead(bool) = 0;

    int getWidth() { return width;}
    int getHeight() { return height;}

    virtual unsigned int getColorTexture() = 0;
    virtual unsigned int getDepthTexture() = 0;
};

#endif //DUMBERENGINE_IFBO_HPP
