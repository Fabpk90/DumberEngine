//
// Created by fab on 09/04/2020.
//

#ifndef DUMBERENGINE_POSTPROCESSSTACK_HPP
#define DUMBERENGINE_POSTPROCESSSTACK_HPP

#include <list>
#include "IPostProcess.hpp"

class PostProcessStack
{
private:
    std::list<IPostProcess*> stack;

public:
    PostProcessStack() = default;

    void addPostProcess(IPostProcess* pp);
    const std::list<IPostProcess*>& getStack() { return stack; }
};
#endif //DUMBERENGINE_POSTPROCESSSTACK_HPP
