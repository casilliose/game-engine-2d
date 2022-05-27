class Empty : public AbstractObjects
{
    public:
        Empty(unsigned short x, unsigned short y, bool solid, string view) {
            this->setCoordinatsX(x, y);
            this->setSolid(solid);
            this->setView(view);
            this->type = 4;
        }

        void print()
        {
            cout << this->view;
        }
};