#include <iostream>
#include <string>

using namespace std;

class tes
{
    private:
        int value = 0;
    public: 
        tes(int value_)
        {
            value = value_;
        }
        void tesOut()
        {
            cout<<"Tes Out "<<value<<endl;
        }
};

class tes2
{
    tes coba = tes(2);
    public :
        void tes22()
        {
            coba.tesOut();
        }
};

int main()
{
    tes2 tesss;
    tesss.tes22();
    return 0;
}