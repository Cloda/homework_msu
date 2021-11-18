#pragma once
#define SIZE 100

#include <iostream>
using namespace std;
 
template <class Type>
struct Vec_Item
{
    Type value; // значение
    Vec_Item *next; // указатель на следующий элемент
    Vec_Item() {next = nullptr;}
};


template <class Type>
class _Vector
{
    private:
        Vec_Item <Type> *_top; // указатель последний элемент

        int _size; // заполнненость
        int _mem; // всего размер

    public:

        // по умолчанию
        _Vector(){
            _top = nullptr;
            _mem = 0;
            _size = 0;
        }

        // по умолчанию размер стека
        _Vector(int n){   
            _top = nullptr;
            if(n <= 0){
                _mem = 0;
            } else if(n >= SIZE){
                _mem = SIZE;
            } else {
                _mem = n;
                
            }
            _size = 0;
        }

        // деструктор(переписать)
        ~_Vector(){
            while (_top) { del(); }
        }

        // поместить элемент в стек(переписать)
        int push(Type &obj){
            if(_mem == 0) return -1;
            if(_size == _mem) return -2;
            try {
                Vec_Item<Type> *pos = new Vec_Item<Type>;
                pos->value = obj; // аналог pos->value ~~~ (*pos).value
                pos->next = _top; // у созданного элемента вектора указатель на следующий будет на предыдущий
                _top = pos;
                ++_size;
            } catch (std::bad_alloc) {
                return -3; 
            }
            return 1;
        }

        // удалить последний элемент в векторе
        int del(){
            if (_size == 0) return 0;

            Vec_Item<Type> *p = _top;
            _top = _top->next;
            delete p;
            --_size;
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

        // шаблон нужен новый, тк это дружественный оператор к нашему к классу и не понятно над какой структурой будем работать
        template <class P>
        friend ostream & operator<<(ostream& os, const _Vector<P> & st){
            os << "vector: ";
            for (Vec_Item<Type> *p = st._top; p; p = p->next)
            {
                os << p->value << " ";
            }
            os << endl;
            return os;
        }

        // взятие по индексу(переписать) реализовать индекс по модулю(как в питоне)
        Type & operator[](int index){
            assert(index >= 0 && index < _size);
            int count = _size - 1;
            Type *result;

            for (Vec_Item<Type> *p = this->_top; p; p = p->next)
            {
                if(count == index){
                    result = &(p->value);
                    break;
                }
                count--;
            }
            return *result;
        }
};

