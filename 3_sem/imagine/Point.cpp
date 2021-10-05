#include "Point.h" 
		
Point::Point(){
	len = 0;
	mass = NULL;
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
	delete [] list;
}

Point::~Point(){
	len = 0;
	mass = NULL;
}

// принт точек
void Point::Print(){
	for(int i = 0; i < len; i++){
		cout << "Ваши точки из массива:" << endl;
		cout << mass[i] << " ";
	}
	cout << endl;
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

Point operator+(const Point &a, const Point &b){
	int n1 = a.len;
	int n2 = b.len;
	int i = 0, j = 0, flag = 1, postLen = 0;

	double *listRes = new double[n1 + n2];

	for(i = 0; i < n1; i += 2){
		for(j = 0; j < n2; j += 2){
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

	for(i = 0; i < n2; i += 2){
		for(j = 0; j < n1; j += 2){
			if(b.mass[i] == a.mass[j] && b.mass[i + 1] == a.mass[j + 1]){
				listRes[postLen] = b.mass[i];
				listRes[postLen + 1] = b.mass[i + 1];
				postLen += 2;
				flag = 0;
				break;
			}
		}
		if (flag){
			listRes[postLen] = b.mass[i];
			listRes[postLen + 1] = b.mass[i + 1];
			postLen += 2;
		}
		flag = 1;
	}

	return Point(listRes, postLen);
}

const Point & Point::operator=(const Point &b){
	len = b.len;
	mass = new double[len];

	for(int i = 0; i < len; i++){
		mass[i] = b.mass[i];
	}

   	return *this;
}

Point operator-(const Point &a, const Point &b){
	int n1 = a.len;
	int n2 = b.len;
	int i = 0, j = 0, flag = 1, postLen = 0;
	double *listRes = new double[n1];
	for(i = 0; i < n1; i += 2){
		for(j = 0; j < n2; j += 2){
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
	return Point(listRes, postLen);
}

Point operator*(const Point &a, const Point &b){

	int n3 = 0;
	int n1 = a.len;
	int n2 = b.len;
	int i = 0, j = 0, k = 0;
	int flag = 1;
	
	double *listRes;
	double A1, B1, C1;
	double A2, B2, C2;
	
	double x, y;
	
	int step1 = 2;
	int step2 = 2;
	
	if(n1 == 4){
		step1 = 4;
	}
	
	if(n2 == 4){
		step2 = 4;
	}
	
	// проверка на равенство экземпляров класса
	if(a == b){
		return Point(a.mass, n1);
	}
	
	// цикл с подсчетом количества пересечений
	for(i = 0; i < n1; i=i+step1)
	{
		B1 = a.mass[i%n1] - a.mass[(i+2)%n1];
		A1 = a.mass[(i+1)%n1] - a.mass[(i+3)%n1];
		C1 = a.mass[i%n1]*a.mass[(i+3)%n1] - a.mass[(i+2)%n1]*a.mass[(i+1)%n1];
		
		for(j = 0; j < n2; j=j+step2)
		{
			B2 = b.mass[j%n2] - b.mass[(j+2)%n2];
			A2 = b.mass[(j+1)%n2] - b.mass[(j+3)%n2];
			C2 = b.mass[j%n2]* b.mass[(j+3)%n2] - b.mass[(j+2)%n2]*b.mass[(j+1)%n2];
			
			if((A2*B1 - A1*B2) == 0)//paralell проверить на совпадение 
			{
				if(A2*a.mass[i%n1] - B2*a.mass[(i+1)%n1] + C2 != 0){	
					break;
				}
				
				if(	A2*a.mass[i%n1] - B2*a.mass[(i+1)%n1] + C2 == 0 &&
					
					a.mass[i%n1] >= min(min(a.mass[i%n1] , a.mass[(i+2)%n1]), min(b.mass[j%n2], b.mass[(j+2)%n2]))&&
					a.mass[i%n1] <= max(max(a.mass[i%n1] , a.mass[(i+2)%n1]), max(b.mass[j%n2], b.mass[(j+2)%n2]))&&
				

					a.mass[(i+2)%n1] >= min(min(a.mass[i%n1] , a.mass[(i+2)%n1]), min(b.mass[j%n2], b.mass[(j+2)%n2]))&&
					a.mass[(i+2)%n1] <= max(max(a.mass[i%n1] , a.mass[(i+2)%n1]), max(b.mass[j%n2], b.mass[(j+2)%n2]))&&
					
					b.mass[j%n1] >= min(min(a.mass[i%n1] , a.mass[(i+2)%n1]), min(b.mass[j%n2], b.mass[(j+2)%n2]))&&
					b.mass[j%n1] <= max(max(a.mass[i%n1] , a.mass[(i+2)%n1]), max(b.mass[j%n2], b.mass[(j+2)%n2]))&&
				

					b.mass[(j+1)%n1] >= min(min(a.mass[i%n1] , a.mass[(i+2)%n1]), min(b.mass[j%n2], b.mass[(j+2)%n2]))&&
					b.mass[(j+1)%n1] <= max(max(a.mass[i%n1] , a.mass[(i+2)%n1]), max(b.mass[j%n2], b.mass[(j+2)%n2]))&&
					
					a.mass[(i+1)%n1] >= min(min(a.mass[(i+1)%n1] , a.mass[(i+3)%n1]), min(b.mass[(j+1)%n2], b.mass[(j+3)%n2]))&&
					a.mass[(i+1)%n1] <= max(max(a.mass[(i+1)%n1] , a.mass[(i+3)%n1]), max(b.mass[(j+1)%n2], b.mass[(j+3)%n2]))&&
				
				
					a.mass[(i+3)%n1] >= min(min(a.mass[(i+1)%n1] , a.mass[(i+3)%n1]), min(b.mass[(j+1)%n2], b.mass[(j+3)%n2]))&&
					a.mass[(i+3)%n1] <= max(max(a.mass[(i+1)%n1] , a.mass[(i+3)%n1]), max(b.mass[(j+1)%n2], b.mass[(j+3)%n2]))&&
				
					
					b.mass[(j+1)%n1] >= min(min(a.mass[(i+1)%n1] , a.mass[(i+3)%n1]),min( b.mass[(j+1)%n2], b.mass[(j+3)%n2]))&&
					b.mass[(j+1)%n1] <= max(max(a.mass[(i+1)%n1] , a.mass[(i+3)%n1]), max(b.mass[(j+1)%n2], b.mass[(j+3)%n2]))&&
				
				
					b.mass[(j+3)%n1] >= min(min(a.mass[(i+1)%n1] , a.mass[(i+3)%n1]), min(b.mass[(j+1)%n2], b.mass[(j+3)%n2]))&&
					b.mass[(j+3)%n1] <= max(max(a.mass[(i+1)%n1] , a.mass[(i+3)%n1]), max(b.mass[(j+1)%n2], b.mass[(j+3)%n2])))
				{	
					n3=n3+4;
				}
			}
			
			x = (C1*B2 - C2*B1)/(A2*B1 - A1*B2);
			
			// проверка на равенство нуля
			if(B1 != 0){ 
				y = (-A1*x - C1)/-B1;
			} else if(B2 != 0){
				y = (-A2*x  - C2)/-B2;
			} else if(B1 == B2 == 0){
				y = 0;
			} else if(A1 == A2 == 0){
				x = 0;
			}
			
			// проверка точки на принадлежание отрезкам
			if( x >= min(a.mass[i%n1] , a.mass[(i+2)%n1])  && 
				x <= max(a.mass[i%n1] , a.mass[(i+2)%n1]) &&
				y >= min(a.mass[(i+1)%n1] , a.mass[(i+3)%n1]) && 
				y <= max(a.mass[(i+1)%n1] , a.mass[(i+3)%n1]))
			{
				n3=n3+2;
			}
		}
	}
	
	// массив с найденными точками пересечения
	listRes = new double[n3];

	// их нахождение 
	for(i = 0; i < n1; i=i+step1)
	{
		B1 = a.mass[i%n1] - a.mass[(i+2)%n1];
		A1 = a.mass[(i+1)%n1] - a.mass[(i+3)%n1];
		C1 = a.mass[i%n1]*a.mass[(i+3)%n1] - a.mass[(i+2)%n1]*a.mass[(i+1)%n1];
			
		for(j = 0; j < n2; j=j+step2)
		{
			B2 = b.mass[j%n2] - b.mass[(j+2)%n2];
			A2 = b.mass[(j+1)%n2] - b.mass[(j+3)%n2];
			C2 = b.mass[j%n2]* b.mass[(j+3)%n2] - b.mass[(j+2)%n2]*b.mass[(j+1)%n2];
			
			if((A2*B1 - A1*B2) == 0)
			{
				if(A2*a.mass[i%n1] - B2*a.mass[(i+1)%n1] + C2 != 0){
					break;
				}
				
				if(A2*a.mass[i%n1] - B2*a.mass[(i+1)%n1] + C2 == 0 &&
					
					
					a.mass[i%n1] >= min(min(a.mass[i%n1] , a.mass[(i+2)%n1]), min(b.mass[j%n2], b.mass[(j+2)%n2]))&&
					a.mass[i%n1] <= max(max(a.mass[i%n1] , a.mass[(i+2)%n1]), max(b.mass[j%n2], b.mass[(j+2)%n2]))&&
				

					a.mass[(i+2)%n1] >= min(min(a.mass[i%n1] , a.mass[(i+2)%n1]), min(b.mass[j%n2], b.mass[(j+2)%n2]))&&
					a.mass[(i+2)%n1] <= max(max(a.mass[i%n1] , a.mass[(i+2)%n1]), max(b.mass[j%n2], b.mass[(j+2)%n2]))&&
					
					b.mass[j%n1] >= min(min(a.mass[i%n1] , a.mass[(i+2)%n1]), min(b.mass[j%n2], b.mass[(j+2)%n2]))&&
					b.mass[j%n1] <= max(max(a.mass[i%n1] , a.mass[(i+2)%n1]), max(b.mass[j%n2], b.mass[(j+2)%n2]))&&
				

					b.mass[(j+1)%n1] >= min(min(a.mass[i%n1] , a.mass[(i+2)%n1]), min(b.mass[j%n2], b.mass[(j+2)%n2]))&&
					b.mass[(j+1)%n1] <= max(max(a.mass[i%n1] , a.mass[(i+2)%n1]), max(b.mass[j%n2], b.mass[(j+2)%n2]))&&
					
					a.mass[(i+1)%n1] >= min(min(a.mass[(i+1)%n1] , a.mass[(i+3)%n1]), min(b.mass[(j+1)%n2], b.mass[(j+3)%n2]))&&
					a.mass[(i+1)%n1] <= max(max(a.mass[(i+1)%n1] , a.mass[(i+3)%n1]), max(b.mass[(j+1)%n2], b.mass[(j+3)%n2]))&&
				
				
					a.mass[(i+3)%n1] >= min(min(a.mass[(i+1)%n1] , a.mass[(i+3)%n1]), min(b.mass[(j+1)%n2], b.mass[(j+3)%n2]))&&
					a.mass[(i+3)%n1] <= max(max(a.mass[(i+1)%n1] , a.mass[(i+3)%n1]), max(b.mass[(j+1)%n2], b.mass[(j+3)%n2]))&&
				
					
					b.mass[(j+1)%n1] >= min(min(a.mass[(i+1)%n1] , a.mass[(i+3)%n1]),min( b.mass[(j+1)%n2], b.mass[(j+3)%n2]))&&
					b.mass[(j+1)%n1] <= max(max(a.mass[(i+1)%n1] , a.mass[(i+3)%n1]), max(b.mass[(j+1)%n2], b.mass[(j+3)%n2]))&&
				
				
					b.mass[(j+3)%n1] >= min(min(a.mass[(i+1)%n1] , a.mass[(i+3)%n1]), min(b.mass[(j+1)%n2], b.mass[(j+3)%n2]))&&
					b.mass[(j+3)%n1] <= max(max(a.mass[(i+1)%n1] , a.mass[(i+3)%n1]), max(b.mass[(j+1)%n2], b.mass[(j+3)%n2])))
				{
					listRes[k] = max(min(a.mass[i%n1] , a.mass[(i+2)%n1]), min(b.mass[j%n2], b.mass[(j+2)%n2]));
					listRes[k+1] = max(min(a.mass[(i+1)%n1] , a.mass[(i+3)%n1]),min( b.mass[(j+1)%n2], b.mass[(j+3)%n2]));
					
					listRes[k+2] = min(max(a.mass[i%n1] , a.mass[(i+2)%n1]), max(b.mass[j%n2], b.mass[(j+2)%n2]));
					listRes[k+3] = min(max(a.mass[(i+1)%n1] , a.mass[(i+3)%n1]), max(b.mass[(j+1)%n2], b.mass[(j+3)%n2]));
					
					k = k + 4;
				}	
			}
			
			// найденная точка
			x = (C1*B2 - C2*B1)/(A2*B1 - A1*B2);

			if(B1 != 0){ 
				y = (-A1*x - C1)/-B1;
			} else if(B2 != 0){
				y = (-A2*x  - C2)/-B2;
			} else if(B1 == B2 == 0){
				y = 0;
			} else if(A1 == A2 == 0){
				x = 0;
			}
			
			// занесение их в массив
			if( x >= min(a.mass[i%n1] , a.mass[(i+2)%n1])  && 
				x <= max(a.mass[i%n1] , a.mass[(i+2)%n1]) &&
				y >= min(a.mass[(i+1)%n1] , a.mass[(i+3)%n1]) && 
				y <= max(a.mass[(i+1)%n1] , a.mass[(i+3)%n1]))
			{
				listRes[k] = x;
				listRes[k+1] = y;
				k = k + 2;
			}
		}
	}

	return Point(listRes, n3);
	
}

// занесение точек в файл
void Point::toFile(){
	FILE *f;
	cout << "Enter name file: ";
	cin >> nameOfFile;

	f = fopen(nameOfFile.c_str(), "w");
	for(int i = 0; i < len; i+=2){
		fprintf(f, "%lf %lf\n", mass[i], mass[i + 1]);
	}
	fclose(f);
}

// отрисовка точек
void Point::DrawDot(){
	if (nameOfFile.length() != 0){
		string str = "plot \"" + nameOfFile + "\" using 1:2\n";
		FILE *pipe = popen(GNUPLOT_NAME, "w");

		if (pipe != NULL){
			fprintf(pipe, "%s", str.c_str());
			fflush(pipe);

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

	
