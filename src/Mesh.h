#pragma once

#include <string>
#include <vector>
#include <memory>

using namespace std;

namespace tfw
{
    class Mesh
    {
    public:
        typedef shared_ptr<Mesh> Ptr;

        const string& getName() const;
        const vector<float>& getVertices() const;
        const vector<float>& getNormals() const;
        const vector<float>& getUVs() const;
        const vector<float>& getColors() const;

        unsigned int vertBuf = -1;
        unsigned int normalBuf = -1;
        unsigned int uvBuf = -1;
        unsigned int colorBuf = -1;

        void genNormals();

    protected:

        string name;
        vector<float> vertices;
        vector<float> normals;
        vector<float> uvs;
        vector<float> colors;
    };
}
