//
// Created by fab on 15/03/2021.
//

#ifndef DUMBERENGINE_IGBUFFER_HPP
#define DUMBERENGINE_IGBUFFER_HPP

#include <vector>

class IGBuffer
{
public:
    enum class Param : int
    {
        Albedo,
        Normal,
        Depth,
        Position // in uv space
    };

    IGBuffer() = default;
    virtual ~IGBuffer() = default;

    virtual void activate() = 0;
    virtual void bind() = 0;

    virtual void deActivate(){ isActive = false;}

    virtual unsigned int getID(Param textureType) = 0;

    std::vector<Param>& getDescriptors() { return descriptor;}

    bool getIsActive() { return isActive;}

    std::string getDescriptorName(unsigned int index)
    {
        switch (descriptor[index])
        {
            case Param::Albedo:
                return "Albedo";
            case Param::Normal:
                return  "Normal";
            case Param::Depth:
                return "Depth";
            case Param::Position:
                return "Position";
            default:
                return "BADTEXFORMAT";
        }
    }

    std::string getDescriptorName(Param& p)
    {
        auto it = std::find(descriptor.begin(), descriptor.end(), p);

        return getDescriptorName(it - descriptor.begin());
    }

protected:
   std::vector<Param> descriptor;

   //todo: add a system to know which gbuffer is active
   //todo: maybe we can only have one ?
   //todo: but we have to handle toggling between forward and deferred
   bool isActive;
};

#endif //DUMBERENGINE_IGBUFFER_HPP
