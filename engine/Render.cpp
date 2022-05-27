class Render
{
    private:
        Scene scene;

    public:
        Render (Scene scene) {
            this->scene = scene;
        }

        void Write() {
            vector<vector<AbstractObjects*>> map = this->scene.getMap();
            unsigned short x = this->scene.getSizeX();
            unsigned short y = this->scene.getSizeY();
            for(int i = 0; i < map.size(); ++i) {
                for(int j = 0; j < map[i].size(); ++j)
                    map[i][j]->print();
                cout << endl;
            }
        }
};