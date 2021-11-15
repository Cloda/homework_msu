#ifndef VECTOR_NONDEFAULT
#define VECTOR_NONDEFAULT
#define SIZE 100

#include <iostream>
using namespace std;
 

template <class Type>
class _Vector
{
    private:
        Type *_vectorPtr; // указатеь на вектор
        Type *_index; // указатель на элемент
        int _size; // размер в 
        int _mem; // всего размер

    public:

        // по умолчанию
        _Vector(){
            _vectorPtr = NULL;
            _vectorPtr = _index;
            _size = 0;
        }

        // по умолчанию размер стека
        _Vector(int n){   
            if(n <= 0){
                _vectorPtr = NULL;
                _mem = 0;
            } else if(n >= SIZE){
                _vectorPtr = new Type[SIZE + 1];
                _mem = SIZE + 1;
            } else{
                _vectorPtr = new Type[n + 1];
                _mem = n + 1;
                
            }
            _index = _vectorPtr;
            _size = 0;
        }

        // деструктор
        ~_Vector(){
            delete [] _vectorPtr; // удаляем стек
            _index = NULL;
            _vectorPtr = NULL;
        }

        // поместить элемент в стек
        int push(Type value){
            if(_size == _mem - 1){
                return -1;
            }       
            *(_index) = value;
            _index += 1;
            _size += 1;

            return 1;
        }

        // удалить последний элемент в векторе
        int delEnd(){
            if(!_size){
                return -1;
            }       
            _index -= 1;
            _size -= 1;
        
            return 1;
        }

        // размер вектора
        int getLen(){
            return _mem;
        }

        // пустота вектора
        int isEmpty(){
            return _size == 0;
        }

        // есть ли еще место
        int isMemory(){
            if(_size < _mem){
                return 1;
            }
            return 0;
        }
    
        //принт вектора
        void print(){
            for (static int i = 0; i < _size; i++){
                cout << *_vectorPtr + i << endl;
            }
        }   

        // взятие по индексу
        Type& operator[](int index)
        {
            assert(index >= 0 && index < _mem);
            return *(_vectorPtr + index);
        }
};


#endif