class Scene
{
    protected:
        uint16_t x;
        uint16_t y;
        vector<vector<AbstractObjects*>> map;
        struct eatCurrentCoortinat {
            int x;
            int y;
        };
        std::map<uint16_t, eatCurrentCoortinat> currentObject;
       

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
            if (item->getTypeObject() == 3) {
                eatCurrentCoortinat eatCur {x,y};
                currentObject.insert({x+y, eatCur});
            }
            map[x][y] = item;
        }

        void removeItemMap(uint16_t x, uint16_t y)
        {
            map[x][y] = nullptr;
        }

        void removeEatForBot(uint16_t x, uint16_t y)
        {
            if (currentObject.count(x+y)) {
                currentObject.erase(x+y);
            }
        }

        auto getByCoordinat(uint16_t x, uint16_t y)
        {
            return map[x][y];
        }

        uint16_t getClosestByCoordinates(uint16_t x, uint16_t y)
        {
            uint16_t saveItem {0}, minStepItem {500}, firstItem;
            for (auto const& item : currentObject)
            {
                saveItem = fabs(x - item.second.x) + fabs(y - item.second.y);
                if (saveItem <= 2) {
                    return item.first;
                }
                if (minStepItem > saveItem) {
                    minStepItem = saveItem;
                    firstItem = item.first;
                }
            }
            return firstItem;
        }

        std::tuple<uint16_t, uint16_t> getNewCoordinatesForBot(uint16_t x, uint16_t y)
        {
            uint16_t first = getClosestByCoordinates(x, y);
            auto item = currentObject[first];
            uint16_t newX {x}, newY {y};
            srand(time(NULL));
            if (rand() % 3 >= 1) {
                if (x != item.x) {
                    if (x - item.x > 0) {
                        newX--;
                    } else {
                        newX++;
                    }
                } else if (y != item.y) {
                    if (y - item.y > 0) {
                        newY--;
                    } else {
                        newY++;
                    }
                }
            } else {
                if (y != item.y) {
                    if (y - item.y > 0) {
                        newY--;
                    } else {
                        newY++;
                    }
                } else if (x != item.x) {
                    if (x - item.x > 0) {
                        newX--;
                    } else {
                        newX++;
                    }
                }
            }
            return std::make_tuple(newX, newY);
        }
};
