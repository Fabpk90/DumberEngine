//
// Created by fab on 25/11/2020.
//

#ifndef DUMBERENGINE_IDRAGNDROP_HPP
#define DUMBERENGINE_IDRAGNDROP_HPP

class IDragNDrop
{
public:
    virtual void OnFileDropped(const char* path) = 0;
};

#endif //DUMBERENGINE_IDRAGNDROP_HPP
