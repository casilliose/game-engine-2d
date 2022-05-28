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
            for(int i = 0; i < x; ++i) {
                for(int j = 0; j < y; ++j)
                    if (map[i][j])
                        map[i][j]->print();
                    else
                        cout << "  ";
                cout << endl;
            }
        }
};