#include "MeshCache.h"

#include "Cube.h"

using namespace tfw;

Mesh::Ptr MeshCache::getMesh(const string& name)
{
    Mesh::Ptr mesh = nullptr;
    auto cacheEntry = cache.find(name);
    if (cacheEntry == cache.end()) {
        mesh = buildMesh(name);
        if (mesh != nullptr) {
            cache[name] = mesh;
        }
    }
    else {
        mesh = cacheEntry->second;
    }
    return mesh;
}

Mesh::Ptr MeshCache::buildMesh(const string& name)
{
    Mesh::Ptr mesh = nullptr;
    if (name == "cube") {
        mesh = make_shared<Cube>();
    }
    return mesh;
}
