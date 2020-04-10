//
// Created by fab on 09/04/2020.
//

#include "../../../headers/rendering/postprocess/PostProcessStack.hpp"

void PostProcessStack::addPostProcess(IPostProcess *pp)
{
    stack.push_front(pp);
}

