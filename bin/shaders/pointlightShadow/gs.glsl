#version 400

layout(triangles) in;
layout(triangle_strip, max_vertices=18) out;

uniform mat4 shadowMatrices[6];

out vec4 fragPos;

void main()
{
    for(int face = 0; face < 6; ++face)
    {
        //used as an index for the cubemap
        gl_Layer = face;

        for(int triangle = 0; triangle < 3; ++triangle)
        {
            //we send the position to compute the depth
            fragPos = gl_in[triangle].gl_Position;
            //transforming the vertex in cube face space
            gl_Position = shadowMatrices[face] * fragPos;
            EmitVertex();
        }

        EndPrimitve();
    }
}
