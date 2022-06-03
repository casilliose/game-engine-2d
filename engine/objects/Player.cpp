class Player : public AbstractObjects
{
    public:
        Player(uint16_t x, uint16_t y, bool solid, string view) {
            const uint8_t typePlayer {2}; 
            this->setCoordinats(x, y);
            this->setSolid(solid);
            this->setView(view);
            type = typePlayer;
        }

        Player() = default;

        void print()
        {
            cout << view;
        }

        uint16_t getScorePoints()
        {
            return 0;
        }
};
