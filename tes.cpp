#include <iostream>
#include <string>

using namespace std;

class tes
{
    private:
        int value = 0;
    public: 
        tes(){}
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
    tes coba;
    public :
        tes2(){}
        tes2(int value = 0)
        {
            coba = tes(value);
        }
        void tes22()
        {
            coba.tesOut();
        }
};

int main()
{
    tes2 tesss(20);
    tesss.tes22();
    return 0;
}