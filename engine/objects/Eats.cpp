class Eats : public AbstractObjects
{
    private:
        uint16_t scorePoints = 0;

    public:

    Eats(uint16_t x, uint16_t y, bool solid, string view) {
        const uint8_t typeEat {3}; 
        this->setCoordinats(x, y);
        this->setSolid(solid);
        this->setView(view);
        type = typeEat;
    }

    uint16_t getScorePoints() {
        return scorePoints;
    }

    void setScorePoints(uint16_t point) {
        scorePoints = point;
    }

    void print() {
        cout << view;
    }
};
