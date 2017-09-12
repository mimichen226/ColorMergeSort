// color-rgb.h

class Color
{
    public:
        // Constructor
        Color();
        Color(int, int, int);
        // Destructor
        ~Color();

        void setrgb(int, int, int);

        int getr();
        int getg();
        int getb();
        int getmaxrgb();
        int getminrgb();
        int gethue();

        void print();

    private:
        int r;
        int g;
        int b;
        int hue;
};

