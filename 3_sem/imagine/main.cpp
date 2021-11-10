#include "Paralleg.h"

using namespace std;

int main(void){
    Paralleg test(0, 0, 3, 4, 0, 1, 5, 1);
    Paralleg test1(1, 1, 3, 4, 0, 1, 5, 1);
    Point test3 = test * test1;
    test3.DrawDot();
    return 0;
}