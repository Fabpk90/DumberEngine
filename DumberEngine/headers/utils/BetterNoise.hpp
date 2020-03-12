//
// Created by fab on 12/03/2020.
//

#ifndef DUMBERENGINE_BETTERNOISE_HPP
#define DUMBERENGINE_BETTERNOISE_HPP

#include "PerlinNoise.hpp"
#include "Utilities.hpp"

class BetterNoise : public PerlinNoise
{
public :
    float zDecayZMax;
    float zDecayCut;
    bool doPenaltyBottom;
    bool doPenaltyMiddle;
    bool doPenaltySky;

    BetterNoise();

public :
    void setZDecay(float zMax, float cut)
    {
        zDecayZMax = zMax;
        zDecayCut = min(max(0, cut), 1);
    }

    float sample(float xBase, float yBase, float zBase) override ;

};

#endif //DUMBERENGINE_BETTERNOISE_HPP
