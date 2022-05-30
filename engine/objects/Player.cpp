class Player : public AbstractObjects
{
    public:
        Player(unsigned short x, unsigned short y, bool solid, string view) {
            this->setCoordinats(x, y);
            this->setSolid(solid);
            this->setView(view);
            this->type = 2;
        }

        Player() = default;

        void print()
        {
            cout << this->view;
        }

        unsigned short getScorePoints()
        {
            return 0;
        }
};
