//
// Created by fab on 27/02/2020.
//

#ifndef DUMBERENGINE_PERLINNOISE_HPP
#define DUMBERENGINE_PERLINNOISE_HPP

#include <glm/glm.hpp>
#include <cmath>

class PerlinNoise
{
private:
    glm::vec3 * Gradients;
    int Width;
    int Size;
    float Freq;

    void updateVecs();

public:

    ~PerlinNoise();

    PerlinNoise();



    float lerp(float a, float b, float alpha) {
        float alphaSmooth = alpha * (3 * alpha - 2 * alpha*alpha);
        return (1 - alphaSmooth)*a + alphaSmooth * b;
    }

    void setFreq(float freq)
    {
        Freq = freq;
    }

    virtual float sample(float xBase, float yBase, float zBase);
};

#endif //DUMBERENGINE_PERLINNOISE_HPP
