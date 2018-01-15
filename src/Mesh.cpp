#include "Mesh.h"

#include "linmath.h"

using namespace tfw;

const string& Mesh::getName() const
{
    return name;
}

const vector<float>& Mesh::getVertices() const
{
    return vertices;
}

const vector<float>& Mesh::getNormals() const
{
    return normals;
}

const vector<float>& Mesh::getUVs() const
{
    return uvs;
}

const vector<float>& Mesh::getColors() const
{
    return colors;
}

void Mesh::genNormals()
{
    normals.resize(vertices.size());
    int numTris = vertices.size() / 9;
    for (int t = 0; t < numTris; ++t) {
        vec3 edge1, edge2, normal;
        vec3 v1 = { vertices[t*9+0], vertices[t*9+1], vertices[t*9+2] };
        vec3 v2 = { vertices[t*9+3], vertices[t*9+4], vertices[t*9+5] };
        vec3 v3 = { vertices[t*9+6], vertices[t*9+7], vertices[t*9+8] };
        vec3_sub(edge1, v2, v1);
        vec3_sub(edge2, v3, v1);
        vec3_mul_cross(normal, edge1, edge2);
        vec3_norm(normal, normal);
        normals[t*9+0] = normal[0];
        normals[t*9+1] = normal[1];
        normals[t*9+2] = normal[2];
        normals[t*9+3] = normal[0];
        normals[t*9+4] = normal[1];
        normals[t*9+5] = normal[2];
        normals[t*9+6] = normal[0];
        normals[t*9+7] = normal[1];
        normals[t*9+8] = normal[2];
    }
}
