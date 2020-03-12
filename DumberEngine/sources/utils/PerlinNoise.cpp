//
// Created by fab on 27/02/2020.
//

#include "../../headers/utils/PerlinNoise.hpp"
#include "../../headers/utils/Utilities.hpp"

PerlinNoise::PerlinNoise()
{
    width = 41;
    size = width * width * width;
    gradients = new glm::vec3[size];
    updateVecs();
    freq = 1;
}

void PerlinNoise::updateVecs()
{
    for (int i = 0; i < size; i++)
    {
        gradients[i].x = (float)randf();
        gradients[i].y = (float)randf();
        gradients[i].z = (float)randf();
    }
}

float PerlinNoise::sample(float xBase, float yBase, float zBase)
{
    float x = xBase * freq;
    float y = yBase * freq;
    float z = zBase * freq;

    while (x >= width - 1)
        x -= width - 1;
    while (y >= width - 1)
        y -= width - 1;
    while (z >= width - 1)
        z -= width - 1;

    int x1 = (int)floor(x);
    int x2 = (int)floor(x) + 1;
    int y1 = (int)floor(y);
    int y2 = (int)floor(y) + 1;
    int z1 = (int)floor(z);
    int z2 = (int)floor(z) + 1;
    float dx = x - x1;
    float dy = y - y1;
    float dz = z - z1;

    glm::vec3 pos(x, y, z);
    glm::vec3 sommets[8];
    //plan X2
    sommets[0] = glm::vec3((float)x2, (float)y1, (float)z1);
    sommets[1] = glm::vec3((float)x2, (float)y1, (float)z2);
    sommets[2] = glm::vec3((float)x2, (float)y2, (float)z2);
    sommets[3] = glm::vec3((float)x2, (float)y2, (float)z1);

    //plan X1
    sommets[4] = glm::vec3((float)x1, (float)y1, (float)z1);
    sommets[5] = glm::vec3((float)x1, (float)y1, (float)z2);
    sommets[6] = glm::vec3((float)x1, (float)y2, (float)z2);
    sommets[7] = glm::vec3((float)x1, (float)y2, (float)z1);

    float angles[8];
    for (int i = 0; i < 8; i++)
        angles[i] = glm::dot((pos - sommets[i]), gradients[(int)(sommets[i].x * width * width + sommets[i].y * width + sommets[i].z)]);

    //plan X2
    float ybas = lerp(angles[0], angles[3], dy);
    float yhaut = lerp(angles[1], angles[2], dy);
    float mid2 = lerp(ybas, yhaut, dz);

    //plan X1
    ybas = lerp(angles[4], angles[7], dy);
    yhaut = lerp(angles[5], angles[6], dy);
    float mid1 = lerp(ybas, yhaut, dz);

    float res = lerp(mid1, mid2, dx);

    res = (res + 1) / 2.0f;

    //Milieu
    return min(1, max(0, res));
}

PerlinNoise::~PerlinNoise()
{
    delete[] gradients;
}

