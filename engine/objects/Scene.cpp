class Scene
{
    protected:
        uint16_t x;
        uint16_t y;
        vector<vector<AbstractObjects*>> map;

    public:
        Scene (uint16_t x, uint16_t y) {
            this->x = x;
            this->y = y;
            vector<vector<AbstractObjects*>> map{x,vector<AbstractObjects*>{y,nullptr}};
            this->map = map;
        }

        Scene() = default;

        uint16_t getSizeX() {
            return x;
        }
        
        uint16_t getSizeY() {
            return y;
        }

        vector<vector<AbstractObjects*>> getMap()
        {
            return map;
        }

        void setItemMap(uint16_t x, uint16_t y, AbstractObjects* item)
        {
            map[x][y] = item;
        }

        void removeItemMap(uint16_t x, uint16_t y)
        {
            map[x][y] = nullptr;
        }

        auto getByCoordinat(uint16_t x, uint16_t y)
        {
            return map[x][y];
        }
};
