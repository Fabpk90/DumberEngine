//
// Created by fab on 02/05/2020.
//

#ifndef DUMBERENGINE_SHADOWMAPPING_HPP
#define DUMBERENGINE_SHADOWMAPPING_HPP

#include "Fbo.hpp"

class ShadowMapping
{
public:
    void draw();

    ShadowMapping(uint32_t width, uint32_t height);
private:
    Fbo* fbo;

public:
    static ShadowMapping* shadowMapping;
};
#endif //DUMBERENGINE_SHADOWMAPPING_HPP
