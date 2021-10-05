#include "Paralleg.h"

Paralleg::~Paralleg(){
    mass = NULL;
}

Paralleg::Paralleg(){
    mass = NULL;
    len = 0;
}
Paralleg::Paralleg(const Paralleg &a){
    len = a.len;
    mass = a.mass;
}

Paralleg::Paralleg(double x_0, double y_0, double x_1, double y_1, double x_2, double y_2){

    if(x_0 - x_1 == 0 || x_2 - x_1 == 0){
        cout << "fall in data" << endl;
        this->~Paralleg();
    } else {
        int SPLIT = 20;
        len = 8*(SPLIT + 1);
        double *newPoint = new double[len];
        double k1 = (y_0 - y_1)/(x_0 - x_1);
        double k2 = (y_2 - y_1)/(x_2 - x_1);

        int temp = 0;
        double fake;
        for(int i = 0; i <= SPLIT; i++){
            fake = (x_0 - x_1)*((double)i/SPLIT);
            newPoint[temp] = x_1 + fake;
            newPoint[temp + 1] = y_1 + fake*k1;
            temp += 2;
        }

        for(int i = 0; i <= SPLIT; i++){
            fake = x_2*((double)i/SPLIT);
            newPoint[temp] = x_0 + fake;
            newPoint[temp + 1] = y_0 + fake*k2;
            temp += 2;
        }

        for(int i = 0; i <= SPLIT; i++){
            fake = (x_0 - x_1)*((double)i/SPLIT);
            newPoint[temp] = x_2 + fake;
            newPoint[temp + 1] = y_2 + fake*k1;
            temp += 2;
        }

        for(int i = 0; i <= SPLIT; i++){
            fake = (x_2 - x_1)*((double)i/SPLIT);
            newPoint[temp] = x_1 + fake;
            newPoint[temp + 1] = y_1 + fake*k2;
            temp += 2;

        }    
        mass = newPoint;
    }
}


Paralleg::Paralleg(double x_0, double y_0, double x_1, double y_1, double x_2, double y_2, double len_one, double len_two){

    if(x_1 / x_2 ==  y_1 / y_2){
        cout << "fall in data" << endl;
        this->~Paralleg();
    } else {
        int SPLIT = 20;
        len = 8*(SPLIT + 1);
        double *newPoint = new double[len];
        double k1 = (y_1)/(x_1);
        double k2 = (y_2)/(x_2);

        double xnorm1 = x_1/sqrt(x_1*x_1 + y_1*y_1);
        double ynorm1 = y_1/sqrt(x_1*x_1 + y_1*y_1);

        double xnorm2 = x_2/sqrt(x_2*x_2 + y_2*y_2);
        double ynorm2 = y_2/sqrt(x_2*x_2 + y_2*y_2);


        int temp = 0;
        double fake;
        for(int i = 0; i <= SPLIT; i++){
            fake = (len_one)*((double)i/SPLIT);
            newPoint[temp] = x_0 + xnorm1*fake;
            newPoint[temp + 1] = y_0 + ynorm1*fake;
            temp += 2;
        }

        for(int i = 0; i <= SPLIT; i++){
            fake = len_two*((double)i/SPLIT);
            newPoint[temp] = x_0 + xnorm2*fake;
            newPoint[temp + 1] = y_0 + ynorm2*fake;
            temp += 2;

        } 

        for(int i = 0; i <= SPLIT; i++){
            fake = len_two*((double)i/SPLIT);
            newPoint[temp] = x_0 + x_1 + xnorm2*fake;
            newPoint[temp + 1] = y_0 + y_1 + ynorm2*fake;
            temp += 2;
        }

        for(int i = 0; i <= SPLIT; i++){
            fake = len_one*((double)i/SPLIT);
            newPoint[temp] = x_0 + x_2 + xnorm1*fake;
            newPoint[temp + 1] = y_0 + y_2 + ynorm1*fake;
            temp += 2;
        }
        mass = newPoint;
    }
}

Point operator+(const Paralleg &a, const Paralleg &b){
	Point one(a.mass, a.len), two(b.mass, b.len);
	Point res = one + two;
	return res;
}

Point operator*(const Paralleg &a, const Paralleg &b){
	Point one(a.mass, a.len), two(b.mass, b.len);
	Point res = one * two;
	return res;
}

Point operator-(const Paralleg &a, const Paralleg &b){
	Point one(a.mass, a.len), two(b.mass, b.len);
	Point res = one - two;
	return res;
}

