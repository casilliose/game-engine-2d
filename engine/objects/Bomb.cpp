class Bomb : public AbstractObjects
{
    private:
        uint16_t scorePointsRemove {10};

    public:
        Bomb(uint16_t x, uint16_t y, bool solid, string view) {
            const uint8_t typeBomb {7}; 
            this->setCoordinats(x, y);
            this->setSolid(solid);
            this->setView(view);
            type = typeBomb;
        }

        void print() {
            cout << view;
        }

        uint16_t getScorePoints()
        {
            return scorePointsRemove;
        }
};
