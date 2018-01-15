#include <gtest/gtest.h>
#include "MeshCache.h"

TEST(MeshCache, CubeExists)
{
    tfw::MeshCache meshCache;
    tfw::Mesh::Ptr m = meshCache.getMesh("cube");
    ASSERT_TRUE(m != nullptr);
}

TEST(MeshCache, SecondAccessReturnsCached)
{
    tfw::MeshCache meshCache;
    tfw::Mesh::Ptr m1 = meshCache.getMesh("cube");
    tfw::Mesh::Ptr m2 = meshCache.getMesh("cube");
    ASSERT_TRUE(m1 == m2);
}

TEST(MeshCache, MeshHasNormals)
{
    tfw::MeshCache meshCache;
    tfw::Mesh::Ptr m = meshCache.getMesh("cube");
    ASSERT_TRUE(m->getNormals().size() > 0);
}
