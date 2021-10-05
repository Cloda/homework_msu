#ifndef PARALLEG_H
#define PARALLEG_H
// #define SPLIT 20

#include "Point.h"


class Paralleg: public Point{

	public:
        Paralleg();
        Paralleg(double x0, double y0, 
                double x1, double y1,  
                double x2, double y2);
        Paralleg(double x0, double y0, 
                double x1, double y1,  
                double x2, double y2,
                double len_one, double len_two);
        Paralleg(const Paralleg &a);
        ~Paralleg();
	
        friend Point operator+(const Paralleg &a, const Paralleg &b);
        friend Point operator*(const Paralleg &a, const Paralleg &b);
        friend Point operator-(const Paralleg &a, const Paralleg &b);
};

#endif