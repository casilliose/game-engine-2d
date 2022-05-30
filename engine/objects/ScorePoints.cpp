class ScorePoints
{
    private:
        unsigned short scorePoints = 0;
        string view = "";

    public:
        ScorePoints() = default;
        unsigned short getPoints()
        {
            return this->scorePoints;
        }

        void addPoints(unsigned short point)
        {
            this->scorePoints += point;
        }

        void rmPoints(unsigned short point)
        {
            if (this->scorePoints - point <= 0) {
                this->scorePoints = 0;
            }
            this->scorePoints -= point;
        }

        void print()
        {
            cout << this->view << " = " << this->scorePoints;
        }

        void setView(string view)
        {
            this->view = view;
        }
};
