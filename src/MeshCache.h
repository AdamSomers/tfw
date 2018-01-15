#pragma once

#include "Mesh.h"

#include <map>
using namespace std;

namespace tfw
{
    class MeshCache
    {
    public:
        Mesh::Ptr getMesh(const string& name);

    private:
        Mesh::Ptr buildMesh(const string& name);

        map<string, Mesh::Ptr> cache;
    };
}
