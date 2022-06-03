class Walls : public AbstractObjects
{
    public:
        Walls(uint16_t x, uint16_t y, bool solid, string view) {
            const uint8_t typeWalls {1}; 
            this->setCoordinats(x, y);
            this->setSolid(solid);
            this->setView(view);
            type = typeWalls;
        }

        void print()
        {
            cout << view;
        }

        uint16_t getScorePoints()
        {
            return 0;
        }
};