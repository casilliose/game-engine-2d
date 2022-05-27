class Scene
{
    protected:
        unsigned short x;
        unsigned short y;
        vector<vector<AbstractObjects*>> map;

    public:
        Scene (unsigned short x, unsigned short y) {
            this->x = x;
            this->y = y;
            vector<vector<AbstractObjects*>> map{x,vector<AbstractObjects*>{y,nullptr}};
            this->map = map;
        }

        Scene() = default;

        unsigned short getSizeX() {
            return this->x;
        }
        
        unsigned short getSizeY() {
            return this->y;
        }

        vector<vector<AbstractObjects*>> getMap()
        {
            return this->map;
        }

        void setItemMap(unsigned short x, unsigned short y, AbstractObjects* item)
        {
            this->map[x][y] = item;
        }
};