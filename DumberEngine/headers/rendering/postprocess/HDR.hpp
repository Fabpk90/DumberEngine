//
// Created by fab on 02/05/2020.
//

#ifndef DUMBERENGINE_HDR_HPP
#define DUMBERENGINE_HDR_HPP

#include "IPostProcess.hpp"

class HDR : public IPostProcess
{
public:
    void renderEffect(Vbo *vboToRenderTo) override;

    void drawInspector() override;
};
#endif //DUMBERENGINE_HDR_HPP
