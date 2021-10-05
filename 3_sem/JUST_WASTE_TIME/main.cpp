#include "Paralleg.h"


using namespace std;

int main(void){
    double a1, a2, a3, a4, a5, a6, a7, a8;
    cin >> a1;
    cin >> a2;
    cin >> a3;
    cin >> a4;
    cin >> a5;
    cin >> a6;
    cin >> a7;
    cin >> a8;

    Paralleg test(a1, a2, a3, a4, a5, a6, a7, a8);
    test.Print();
    test.DrawDot();

    return 0;
}