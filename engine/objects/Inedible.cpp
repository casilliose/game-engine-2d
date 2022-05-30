class Inedible : public AbstractObjects
{
    public:
        Inedible(unsigned short x, unsigned short y, bool solid, string view) {
            this->setCoordinatsX(x, y);
            this->setSolid(solid);
            this->setView(view);
            this->type = 5;
        }

        void print()
        {
            cout << this->view;
        }
};