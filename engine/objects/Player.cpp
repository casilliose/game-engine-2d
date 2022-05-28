class Player : public AbstractObjects
{
    public:
        Player(unsigned short x, unsigned short y, bool solid, string view) {
            this->setCoordinatsX(x, y);
            this->setSolid(solid);
            this->setView(view);
            this->type = 2;
        }

        void print()
        {
            cout << this->view;
        }
};