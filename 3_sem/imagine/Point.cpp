#include "Point.h" 

Point::Point(){
    mass = new double[2];
    mass[0] = 0.;
    mass[1] = 0.;
    len = 2;
}

Point::~Point(){
	delete [] mass;
	mass = 0;
}

Point::Point(const Point &a){
	int i;
	len = a.len;
	mass = new double[len];
	
	for(i = 0; i < len; i++){
		mass[i] = a.mass[i];
	}
}

Point::Point(double *list, int size){
	int i;
	len = size;
	
	mass = new double[len];
	
	for(i = 0; i < len; i++){
		mass[i] = list[i];
	}
}

// опраторор равенства
const Point & Point::operator=(const Point &b){
	int i;
	len = b.len;
	mass = new double[len];
	
	for(i = 0; i < len; i++){
		mass[i] = b.mass[i];
	}
   	return *this;
}

// перегрузка оператора сравнение 
int operator==(const Point &a, const Point &b){
	int count = 0, flag = 0;
	if(a.len == b.len){
		for(int i = 0; i < a.len; i += 2){
			for(int j = 0; j < b.len; j += 2){
				if(a.mass[i] == b.mass[j] && a.mass[i + 1] == b.mass[j + 1]){
					count += 1;
				}
			}
			if (count == 1){
				flag += 2;
			}
			count = 0;
		}
	} else {
		return 0;
	} 
	if (flag == a.len){
		return 1;
	} else {
		return 0;
	}
}

// перегрузка оператора объединение
Point operator+(const Point &a, const Point &b){
	FILE *f_c;
	string nameOfFile_c;

	int n1 = a.len;
	int n2 = b.len;
	int i = 0, j = 0, flag = 1, number = 0;

	double *listRes = new double[n1 + n2];
	
	for(i = 0; i < n1; i += 2){
		
		listRes[number] = a.mass[i];
		listRes[number + 1] = a.mass[i + 1];
		number += 2;
	
	}

	for(j = 0; j < n2; j += 2){
		
		listRes[number] = b.mass[j];
		listRes[number + 1] = b.mass[j + 1];
		number += 2;
	}
	
	number = n1 + n2;

	
	cout << "Enter name of file:" << endl;
	cin >> nameOfFile_c;


	f_c = fopen(nameOfFile_c.c_str(), "w");
	
	for(int i = 0; i < a.len; i+=2){
		fprintf(f_c, "%lf %lf \n", a.mass[i], a.mass[i + 1]);
	}

	fprintf(f_c,"\n");

	for(int i = 0; i < b.len; i+=2){
		fprintf(f_c, "%lf %lf \n", b.mass[i], b.mass[i + 1]);
	}

	Point c(listRes, number);
	c.nameOfFile = nameOfFile_c;
	
	delete[] listRes;

	fclose(f_c);
	return c;
}

// перегрузка оператора разности
Point operator-(const Point &a, const Point &b){
	int n1 = a.len;
	int n2 = b.len;
	int i = 0, j = 0, flag = 1, postLen = 0;
	double *listRes = new double[n1];
	for(i = 0; i < n1 - 2; i += 2){
		for(j = 0; j < n2 - 2; j += 2){
			if(a.mass[i] == b.mass[j] && a.mass[i + 1] == b.mass[j + 1]){
				flag = 0;
				break;
			}
		}
		if (flag){
			listRes[postLen] = a.mass[i];
			listRes[postLen + 1] = a.mass[i + 1];
			postLen += 2;
		}
		flag = 1;
	}

	Point c;
	if(postLen == 0){
		c = Point();
	} else {
		c = Point(listRes, postLen);
	}
	delete [] listRes;
	listRes = 0;

	c.toFile();
	return c;
}

// еще надо переписать!!!!!!!!!!!!!!!!!!!!!!!!!
// перегрузка оператора пересечения
Point operator*(const Point &a, const Point &b){
	
	int n3 = 0;
	
	int i = 0, j = 0, k = 0;
	
	int n1 = a.len;
	int n2 = b.len;
	
	int step1 = 2;
	int step2 = 2;
	
	double *listRes;
	double A1, B1, C1;
	double A2, B2, C2;
	
	double x, y;
		
	if(a == b){
		return Point(a.mass, n1);
	}
	
	for(i = 0; i < 2 ; i = i + step1)
	{
		
		A1 = a.mass[(i+3)%n1] - a.mass[(i+1)%n1];//y1 y2
		B1 = a.mass[i%n1] - a.mass[(i+2)%n1];//x1 x2
		C1 = a.mass[(i+1)%n1]*(a.mass[(i+2)%n1] - a.mass[i%n1]) - a.mass[i%n1]*(a.mass[(i+3)%n1] - a.mass[(i+1)%n1]) ;

		for(j = 0; j <= n2; j = j + step2)
		{
			
			A2 = b.mass[(j+3)%n2] - b.mass[(j+1)%n2];//y1 y2
			B2 = b.mass[j%n2] - b.mass[(j+2)%n2];//x1 x2
			C2 = b.mass[(j+1)%n2]*(b.mass[(j+2)%n2] - b.mass[j%n2]) - b.mass[j%n2]*(b.mass[(j+3)%n2] - b.mass[(j+1)%n2]) ;
			
			if((A2*B1 - A1*B2) == 0){
				cout << j << endl;
				cout << "(A2*B1 - A1*B2) == 0" << endl;
				break;
			}

			if(A2 == 0){
				x = (C1*B2 - C2*B1)/(A2*B1 - A1*B2);
			}
				
			if(B1 != 0){ 
				y = (-1*(A1*x + C1))/B1;
			}
			else{
				y = (-1*(A2*x  + C2))/B2;
			}
			
			if( ((A1*b.mass[j%n2] + B1*b.mass[(j+1)%n2] + C1)*(A1*b.mass[(j+2)%n2] + B1*b.mass[(j+3)%n2] + C1) < 0) &&
				((A2*a.mass[i%n1] + B2*a.mass[(i+1)%n1] + C2)*(A2*a.mass[(i+2)%n1] + B2*a.mass[(i+3)%n1] + C2) < 0))
			{
					n3=n3+2;
			}
			if( ((A1*b.mass[j%n2] + B1*b.mass[(j+1)%n2] + C1)*(A1*b.mass[(j+2)%n2] + B1*b.mass[(j+3)%n2] + C1) == 0)){
				n3=n3+2;
			}
			if(((A2*a.mass[i%n1] + B2*a.mass[(i+1)%n1] + C2)*(A2*a.mass[(i+2)%n1] + B2*a.mass[(i+3)%n1] + C2) == 0)){
				n3=n3+2;
			}

		}
		
	}

	if(n3 == 0){
		return Point();
	}

	listRes = new double[n3];

	
	for(i = 0; i <= n1 ; i= i +step1)
	{
		A1 = a.mass[(i+3)%n1] - a.mass[(i+1)%n1];//y1 y2
		B1 = a.mass[i%n1] - a.mass[(i+2)%n1];//x1 x2
		C1 = a.mass[(i+1)%n1]*(a.mass[(i+2)%n1] - a.mass[i%n1]) - a.mass[i%n1]*(a.mass[(i+3)%n1] - a.mass[(i+1)%n1]) ;

		for(j = 0; j <= n2; j = j + step2)
		{
			
			A2 = b.mass[(j+3)%n2] - b.mass[(j+1)%n2];//y1 y2
			B2 = b.mass[j%n2] - b.mass[(j+2)%n2];//x1 x2
			C2 = b.mass[(j+1)%n2]*(b.mass[(j+2)%n2] - b.mass[j%n2]) - b.mass[j%n2]*(b.mass[(j+3)%n2] - b.mass[(j+1)%n2]) ;
			
			
			if((A2*B1 - A1*B2) == 0){
				break;
			}

			x = (C1*B2 - C2*B1)/(A2*B1 - A1*B2);

			if(B1 != 0){ 
				y = (-1*(A1*x + C1))/B1;
			} else {
				y = (-1*(A2*x  + C2))/B2;
			}
			
			if( ((A1*b.mass[j%n2] + B1*b.mass[(j+1)%n2] + C1)*(A1*b.mass[(j+2)%n2] + B1*b.mass[(j+3)%n2] + C1) < 0) &&
				((A2*a.mass[i%n1] + B2*a.mass[(i+1)%n1] + C2)*(A2*a.mass[(i+2)%n1] + B2*a.mass[(i+3)%n1] + C2) < 0)
			){
				listRes[k] = x;
				listRes[k+1] = y;
				k = k + 2;
			}

			if( ((A1*b.mass[j%n2] + B1*b.mass[(j+1)%n2] + C1)*(A1*b.mass[(j+2)%n2] + B1*b.mass[(j+3)%n2] + C1) == 0)){
				listRes[k] = x;
				listRes[k+1] = y;
				k = k + 2;
			} 
			if(((A2*a.mass[i%n1] + B2*a.mass[(i+1)%n1] + C2)*(A2*a.mass[(i+2)%n1] + B2*a.mass[(i+3)%n1] + C2) == 0)){
				listRes[k] = x;
				listRes[k+1] = y;
				k = k + 2;
			}

		}
		
	}

	Point new_Point(listRes, n3);
	delete [] listRes;
	listRes = 0;
	
	return new_Point;
}

// занесение точек в файл
void Point::toFile(){
	FILE *f;
	cout << "Enter name file: ";
	cin >> nameOfFile;

	f = fopen(nameOfFile.c_str(), "w");
	for(int i = 0; i < len; i += 2){
		fprintf(f, "%lf %lf\n", mass[i], mass[i + 1]);
	}
	fclose(f);
}

// отрисовка линий
void Point::DrawLines(){
	if (nameOfFile.length() != 0){
		string str = "plot \"" + nameOfFile + "\" with lines\n";
		// cout << str << endl;
		FILE *pipe = popen(GNUPLOT_NAME, "w");

		if (pipe != NULL){
			fprintf(pipe, "%s", str.c_str());
			fflush(pipe);

			// ожидание нажатия клавиши
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			cin.get();

			pclose(pipe);
		}
		else
			cout << "Could not open pipe" << endl;
	} else {
		toFile();
		DrawLines();
	}
}

// отрисовка точек
void Point::DrawDot(){
	if (nameOfFile.length() != 0){
		string str = "plot \"" + nameOfFile + "\" using 1:2\n";
		// cout << str << endl;
		FILE *pipe = popen(GNUPLOT_NAME, "w");

		if (pipe != NULL){
			fprintf(pipe, "%s", str.c_str());
			fflush(pipe);

			// ожидание нажатия клавиши
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			cin.get();

			pclose(pipe);
		}
		else
			cout << "Could not open pipe" << endl;
	} else {
		toFile();
		DrawDot();
	}
}