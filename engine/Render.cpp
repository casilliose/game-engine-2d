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
            uint16_t x = this->scene.getSizeX();
            uint16_t y = this->scene.getSizeY();
            for(size_t i = 0; i < x; ++i) {
                for(size_t j = 0; j < y; ++j)
                    if (map[i][j])
                        map[i][j]->print();
                    else
                        cout << "  ";
                cout << endl;
            }
        }
};