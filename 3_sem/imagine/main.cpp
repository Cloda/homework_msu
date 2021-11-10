#include "Paralleg.h"

using namespace std;

int main(void){
    Paralleg test1(0, 0, 3, 4, 0, 1, 5, 1);
    Paralleg test2(1, 1, 3, 4, 0, 1, 5, 1);
    Point test3 = test1 * test2;
    test3.DrawDot();
    return 0;
}