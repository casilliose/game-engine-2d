class ScorePoints
{
    private:
        int16_t scorePoints {0};
        string view {""};

    public:
        ScorePoints() = default;

        uint16_t getPoints()
        {
            return scorePoints;
        }

        void addPoints(uint16_t point)
        {
            scorePoints += point;
        }

        void rmPoints(uint16_t point)
        {
            if (scorePoints - point <= 0) {
                scorePoints = 0;
                return;
            }
            scorePoints -= point;
        }

        void print()
        {
            cout << view << " = " << scorePoints;
        }

        void setView(string view)
        {
            this->view = view;
        }
};
