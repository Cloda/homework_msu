#include "VectorCustom.h"

int main()
{
    int elem = 102;
    _Vector <int> vec(elem);
    for(int i = 0; i < vec.getLen(); i++){
        vec.push(i);
    }

    vec.print();
 
    return 0;
}