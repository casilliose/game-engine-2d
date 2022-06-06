class Inedible : public AbstractObjects
{
    public:
        Inedible(uint16_t x, uint16_t y, bool solid, string view) {
            const uint8_t typeInedible {5}; 
            this->setCoordinats(x, y);
            this->setSolid(solid);
            this->setView(view);
            type = typeInedible;
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