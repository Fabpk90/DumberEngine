//
// Created by fab on 12/03/2020.
//

#include "../../headers/utils/BetterNoise.hpp"

BetterNoise::BetterNoise() : PerlinNoise()
{
    zDecayZMax = (float)width;
    zDecayCut = 1;
    freq = 1;
    doPenaltyBottom = true;
    doPenaltyMiddle = true;
    doPenaltySky = true;
}

float BetterNoise::sample(float xBase, float yBase, float zBase)
{
    float sample = PerlinNoise::sample(xBase, yBase, zBase);

    //Plus light plus on est haut
    float zDecay_Norm = zBase / zDecayZMax;
    float penalty = 0;
    if (zDecayCut < 1 && zDecayCut >= 0) {
        //Cut au dessus
        if (doPenaltySky)
            penalty = (max(0, zDecay_Norm - zDecayCut));

        //Remplis en dessous
        if (doPenaltyMiddle && zDecay_Norm <= zDecayCut) {
            penalty = (1 - (zDecayCut - zDecay_Norm));
            penalty = -pow(penalty, 20);
            penalty /= 2;
        }

        //Remplis au sol
        if (doPenaltyBottom && zDecay_Norm < 0.1f) {
            penalty = (0.1f - zDecay_Norm) / 0.1f;
            penalty = -pow(penalty, 3);
            penalty /= 4;
        }
    }

    sample -= (penalty / 4.0f);

    return min(1,max(0,sample));
}
