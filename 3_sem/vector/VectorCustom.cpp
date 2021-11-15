// #include "VectorCustom.h"

// // конструктор пустой
// template <typename Type>
// _Vector<Type>::_Vector()
// {
//     _vectorPtr = NULL;
//     _vectorPtr = _index;
//     _size = 0;
// }

// // конструктор
// template <typename Type>
// _Vector<Type>::_Vector(int n)
// {   
//     if(n <= 0){
//         cout << "negative" << endl;
//         _vectorPtr = NULL;
//     } else if(n >= SIZE){
//         _vectorPtr = new Type[SIZE];
//     } else{
//         _vectorPtr = new Type[n];
        
//     }
//     _vectorPtr = _index;
//     _size = 0;
// }
 
// // деструктор
// template <typename Type>
// _Vector<Type>::~_Vector()
// {
//     delete [] _vectorPtr; // удаляем стек
// }
 
// // добавление элемента в динам вектор
// template <typename Type>
// int _Vector<Type>::push(Type value)
// {
//     if(_index == _vectorPtr + SIZE){
//         return -1;
//     }       
//     *(++_index) = value;
//     ++_size;
 
//     return 1;
// }
 
// // удалить последний элемент в векторе
// template <typename Type>
// int _Vector<Type>::delEnd()
// {
//     if(!_size){
//         return -1;
//     }       
//     --_index;
//     --_size;
 
//     return 1;
// }

// template <typename Type> 
// void _Vector<Type>::print()
// {
//     for (static int i = 0; i < _size; i++){
//         cout << *_vectorPtr + i << endl;
//     }
// }