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
        Position
    };

    IGBuffer() = default;
    virtual ~IGBuffer() = default;

    virtual void activate() = 0;
    virtual void bind() = 0;
protected:
   std::vector<Param> descriptor;


};

#endif //DUMBERENGINE_IGBUFFER_HPP
