class Walls : public AbstractObjects
{
    public:
    
    Walls(unsigned short x, unsigned short y, bool solid, string view) {
        this->setCoordinatsX(x, y);
        this->setSolid(solid);
        this->setView(view);
        this->type = 1;
    }

    void print()
    {
        cout << this->view;
    }
};