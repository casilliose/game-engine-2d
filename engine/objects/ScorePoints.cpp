class ScorePoints
{
    public:
        unsigned short scorePoints = 0;

    unsigned short getPoints()
    {
        return this->scorePoints;
    }

    void addPoints(unsigned short point)
    {
        this->scorePoints += point;
    }

    void print()
    {
        cout << this->scorePoints;
    }
};