#include "Paralleg.h"

Paralleg::Paralleg(){
    Point();
}

Paralleg::~Paralleg(){}

Paralleg::Paralleg(const Paralleg &a){
    int i;
    len = a.len;
	mass = new double[len];
    
	for(i = 0; i < len; i++){
		mass[i] = a.mass[i];
	}
}

const Paralleg & Paralleg::operator=(const Paralleg &b){
	len = b.len;
	mass = new double[len];

	for(int i = 0; i < len; i++){
		mass[i] = b.mass[i];
	}
   	return *this;
}

Paralleg::Paralleg(double x_0, double y_0, double x_1, double y_1, double x_2, double y_2){ 
    if(x_0 == x_1 && x_1 == x_2 && y_2 == y_1 && y_2 == y_0){
        cout << "fall in data 0" << endl;
    } else if(x_0 == x_1 && y_1 == y_0 ){
        cout << "fall in data 1" << endl;
    } else if(x_1 == x_2 && y_1 == y_2){
        cout << "fall in data 2" << endl;
    } else if(x_0 == x_2 && y_2 == y_0){
        cout << "fall in data 3" << endl;
    } else if(x_0 == x_2 && x_0 == x_1){
        cout << "fall in data 4" << endl;
    } else if(y_0 == y_2 && y_0 == y_1){
        cout << "fall in data 5" << endl;
    }else {

        int SPLIT = 20;
        len = 8*(SPLIT) + 2;
        double *newPoint = new double[len];
        int temp = 0;
        double fake;

        for(int i = 0; i < SPLIT; i++){
            fake = ((double)i/SPLIT);
            newPoint[temp] = x_1 + fake*x_0;
            newPoint[temp + 1] = y_1 + fake*y_0;
            temp += 2;
        }

        for(int i = 0; i < SPLIT; i++){
            fake = ((double)i/SPLIT);
            newPoint[temp] = x_0 + x_1 + fake*x_2;
            newPoint[temp + 1] =y_0 + y_1 + fake*y_2;
            temp += 2;
        }
        for(int i = 0; i < SPLIT; i++){
            fake = ((double)i/SPLIT);
            newPoint[temp] = x_0 + x_1 + x_2 - fake*x_0;
            newPoint[temp + 1] = y_0 + y_1 + y_2 - fake*y_0;
            temp += 2;
        }
        for(int i = 0; i <= SPLIT; i++){
            fake = ((double)i/SPLIT);
            newPoint[temp] = x_1 + x_2 - fake*x_2;
            newPoint[temp + 1] = y_1 + y_2 - fake*y_2;
            temp += 2;
        } 

        mass = new double[len];
        for(int i = 0; i < len; i++){
            mass[i] = newPoint[i];
        }
        delete[] newPoint;
        newPoint = 0;

        toFile();
    }
}

Paralleg::Paralleg(double x_0, double y_0, double x_1, double y_1, double x_2, double y_2, double len_one, double len_two){

    if(x_1 / x_2 ==  y_1 / y_2){
        cout << "fall in data" << endl;
    } else {
        int SPLIT = 20;
        len = 8*(SPLIT) + 2;
        double *newPoint = new double[len];

        double xnorm1 = x_1/sqrt(x_1*x_1 + y_1*y_1);
        double ynorm1 = y_1/sqrt(x_1*x_1 + y_1*y_1);

        double xnorm2 = x_2/sqrt(x_2*x_2 + y_2*y_2);
        double ynorm2 = y_2/sqrt(x_2*x_2 + y_2*y_2);


        int temp = 0;
        double fake;
        for(int i = 0; i < SPLIT; i++){
            fake = (len_one)*((double)i/SPLIT);
            newPoint[temp] = x_0 + xnorm1*fake;
            newPoint[temp + 1] = y_0 + ynorm1*fake;
            temp += 2;
        }

        for(int i = 0; i < SPLIT; i++){
            fake = len_two*((double)i/SPLIT);
            newPoint[temp] = x_0 + x_1 + xnorm2*fake;
            newPoint[temp + 1] = y_0 + y_1 + ynorm2*fake;
            temp += 2;

        } 

        for(int i = 0; i < SPLIT; i++){
            fake = len_one*((double)i/SPLIT);
            newPoint[temp] = x_0 + x_1 + x_2 - xnorm1*fake;
            newPoint[temp + 1] = y_0 + y_1 + y_2 - ynorm1*fake;
            temp += 2;
        }

        for(int i = 0; i <= SPLIT; i++){
            fake = len_two*((double)i/SPLIT);
            newPoint[temp] = x_0 + x_2 - xnorm2*fake;
            newPoint[temp + 1] = y_0 + y_2 - ynorm2*fake;
            temp += 2;
        }

        mass = new double[len];
        for(int i = 0; i < len; i++){
            mass[i] = newPoint[i];
        }
        delete[] newPoint;
        newPoint = 0;

        toFile();
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

