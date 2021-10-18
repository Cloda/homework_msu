#include "Paralleg.h"


using namespace std;

int main(void){
    // double a1, a2, a3, a4, a5, a6, a7, a8;
    // cin >> a1;
    // cin >> a2;
    // cin >> a3;
    // cin >> a4;
    // cin >> a5;
    // cin >> a6;
    // cin >> a7;
    // cin >> a8;

    // Paralleg test(a1, a2, a3, a4, a5, a6, a7, a8);
    // Paralleg test(a1, a2, a3, a4, a5, a6);
    Paralleg test(0, 0, 4, 3, 2, 0, 5, 2);
    // test.Print();
    // test.toFile();
    // test.DrawDot();
    
    

    // cin >> a1;
    // cin >> a2;
    // cin >> a3;
    // cin >> a4;
    // cin >> a5;
    // cin >> a6;
    // cin >> a7;
    // cin >> a8;
    // Paralleg test1(a1, a2, a3, a4, a5, a6);
    // Paralleg test1(a1, a2, a3, a4, a5, a6, a7, a8);
    Paralleg test1(2, 1.5, 4, 3, 2, 0, 5, 2);
    // test1.Print();
    test1.toFile();
    // test1.DrawDot();
    

    // Point test2(test);
    // Point test2 = test;
    // Point test2 = test1 + test;
    // Point test2 = test1 - test;
    // Point test2 = test1 * test;
    // test2.Print();
    // test2.toFile();
    // test2.DrawDot();

    return 0;
}