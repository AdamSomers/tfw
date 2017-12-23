using namespace std;

namespace tfw
{
    class Scene
    {
    public:
        Scene();
        ~Scene();

        void render();

    private:
        unsigned frameCount = 0;
    };
}
