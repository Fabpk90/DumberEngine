//
// Created by fab on 27/02/2020.
//

#ifndef DUMBERENGINE_PHYSICS_HPP
#define DUMBERENGINE_PHYSICS_HPP

#include <glm/glm.hpp>
#include <glm/vec3.hpp>

class Physics
{
public:

    static bool isIntersecting(glm::vec3 startLine, glm::vec3 endLine, glm::vec3 pointInPlan, glm::vec3 planeNormal, float& t)
    {
        //planeNormal = a,b,c
        // plane equation:  a*x+b*y+z*c+d = 0
        //we take a point on the plan and we dot product it
        // we negate that to have d
        // t = -beta/alpha , t being the lerp between start and end

        float d = glm::dot(-planeNormal, pointInPlan);

        float beta = glm::dot(planeNormal, startLine) + d;
        float alpha = glm::dot(planeNormal, (endLine-startLine));

        if (alpha == 0.0f) return false;

        t = -beta / alpha;

        return t > 0 && t <= 1;
    }

    //uses the fact that if the cross product of the 3 edges of a triangle with the point found are positive (points in the right direction)
    //the point is indeed intersecting the triangle
    static bool isIntersectingTriangle(glm::vec3 startLine, glm::vec3 endLine, glm::vec3 A, glm::vec3 B, glm::vec3 C, glm::vec3 D)
    {
        float t = 0;

        glm::vec3 planNormal = glm::cross(A - B, C - B);

        if (isIntersecting(startLine, endLine, A, planNormal, t))
        {
            glm::vec3 P = startLine + ((endLine - startLine) * t);

            glm::vec3 ABAP = glm::cross(B - A, P - A);
            glm::vec3 BCBP = glm::cross(C - B, P - B);
            glm::vec3 CDCP = glm::cross(D - C, P - C);
            glm::vec3 DADP = glm::cross(A - D, P - D);

            return glm::dot(ABAP, BCBP) >= 0 && glm::dot(BCBP, CDCP) >= 0 && glm::dot(CDCP, DADP) >= 0;
        }
        else
            return false;
    }
};
#endif //DUMBERENGINE_PHYSICS_HPP
