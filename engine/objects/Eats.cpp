class Eats : public AbstractObjects
{
    private:
        unsigned short scorePoints = 0;

    public:

    Eats(unsigned short x, unsigned short y, bool solid, string view) {
        this->setCoordinatsX(x, y);
        this->setSolid(solid);
        this->setView(view);
        this->type = 3;
    }

    unsigned short getScorePoints()
    {
        return this->scorePoints;
    }

    void setScorePoints(unsigned short point)
    {
        this->scorePoints = point;
    }

    void print()
    {
        cout << this->view;
    }
};