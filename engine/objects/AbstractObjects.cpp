using namespace std;
class AbstractObjects
{   
    public:
        virtual void print() = 0;

        void setCoordinatsX(unsigned short x, unsigned short y) {
            this->x = x;
            this->y = y;
        }

        unsigned short getCoordinatX() {
            return this->x;
        }

        unsigned short getCoordinatY() {
            return this->y;
        }

        void setView(string view) {
            this->view = view;
        }

        string getView() {
            return this->view;
        }

        void setSolid(bool solid) {
            this->solid = solid;
        }

        bool getSolid() {
            return this->solid;
        }

        unsigned short getTypeObject()
        {
            return this->type;
        }

    protected:
        unsigned short x;
        unsigned short y;
        bool solid;
        string view;
        unsigned short type;
};