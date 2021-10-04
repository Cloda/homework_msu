#ifndef POINT_H      
#define POINT_H

#include <iostream>
#include <string>
#include <stdio.h>
#include <cstdio>
#include "math.h"

#define MAX 5000
#define GNUPLOT_NAME "gnuplot -persist"


using namespace std;

class Point{
	private :
		double *mass;
		int len;
		string nameOfFile;

	public:
		
		Point();
		Point(double *list, int size);
		Point(const Point &a);
		~Point();

		friend Point operator*(const Point &a, const Point &b);
		friend Point operator+(const Point &a, const Point &b);
		friend Point operator-(const Point &a, const Point &b);
		const Point & operator=(const Point &b);

		void DrawDot();
		void Print();
		void toFile();
		void DrawLines();
};

#endif
