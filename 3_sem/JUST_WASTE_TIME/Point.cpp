
#include "Point.h" 
		
Point::Point(){
	len = 0;
	mass = NULL;
}

Point::Point(const Point &a){
	int i, n;
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
	delete [] mass;
}


void Point::Print(){
	for(int i = 0; i < len; i++){
		cout << mass[i] << " ";
	}
	cout << endl;
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


Point operator*(const Point &a, const Point &b)
{
	
	int n3 = 0;
	int n1 = a.len;
	int n2 = b.len;
	int i = 0, j = 0, k = 0;
	int flag = 1;
	
	double *listRes;
	double A1, B1, C1;
	double A2, B2, C2;
	
	double x, y;
	
	for(i = 0; i < n1; i=i+2)
	{
		for(j = 0; j < n2; j=j+2)
		{
			if(a.mass[i] != b.mass[j] || a.mass[i+1] != b.mass[j+1])
			{
				
				flag = 0;
				
			}
		}
	}
	
	if(flag == 1)
	{
		return Point(a);//!
	}
	
	for(i = 0; i < n1; i=i+2)
	{
		
		B1 = a.mass[i%n1] - a.mass[(i+2)%n1];//x1 x2
		A1 = a.mass[(i+1)%n1] - a.mass[(i+3)%n1];//y1 y2
		C1 = a.mass[i%n1]*a.mass[(i+3)%n1] - a.mass[(i+2)%n1]*a.mass[(i+1)%n1];
		
		//printf("A1 = %f B1 = %f C1 = %f \n", A1, B1, C1);
		
		for(j = 0; j < n2; j=j+2)
		{
			B2 = b.mass[j%n2] - b.mass[(j+2)%n2];//x1 x2
			A2 = b.mass[(j+1)%n2] - b.mass[(j+3)%n2];// y1 y2
			C2 = b.mass[j%n2]*b.mass[(j+3)%n2] - b.mass[(j+2)%n2]*b.mass[(j+1)%n2];
			
			
			//printf("A2 = %f B2 = %f C2 = %f \n", A2, B2, C2);
		
			
			if((A2*B1 - A1*B2) == 0)//paralell
			{
				printf("TEST PARALLEL");
				break;
			}
			
			x = (C1*B2 - C2*B1)/(A2*B1 - A1*B2);
			if(B1 != 0){ 
			y = (-A1*x - C1)/-B1;
			}
			else{
			y = (-A2*x  - C2)/-B2;
			}
			
			
			if( x >= min(a.mass[i%n1] , a.mass[(i+2)%n1])  && 
				x <= max(a.mass[i%n1] , a.mass[(i+2)%n1]) &&
				y >= min(a.mass[(i+1)%n1] , a.mass[(i+3)%n1]) && 
				y <= max(a.mass[(i+1)%n1] , a.mass[(i+3)%n1]) )
				{
					n3=n3+2;
				}
		}
	}

	listRes = new double[n3];
	// printf("test N3 == %d\n", n3);
			
	for(i = 0; i < n1; i=i+2)
	{
		
		B1 = a.mass[i%n1] - a.mass[(i+2)%n1];//x1 x2
		A1 = a.mass[(i+1)%n1] - a.mass[(i+3)%n1];//y1 y2
		C1 = a.mass[i%n1]*a.mass[(i+3)%n1] - a.mass[(i+2)%n1]*a.mass[(i+1)%n1];
			
			
		for(j = 0; j < n2; j=j+2)
		{
			B2 = b.mass[j%n2] - b.mass[(j+2)%n2];//x1 x2
			A2 = b.mass[(j+1)%n2] - b.mass[(j+3)%n2];// y1 y2
			C2 = b.mass[j%n2]*b.mass[(j+3)%n2] - b.mass[(j+2)%n2]*b.mass[(j+1)%n2];
			
			if((A2*B1 - A1*B2) == 0)//paralell
			{
				break;
			}
			
			x = (C1*B2 - C2*B1)/(A2*B1 - A1*B2);
			if(B1 != 0){ 
			y = (-A1*x - C1)/-B1;
			}
			else{
			y = (-A2*x - C2)/-B2;
			}
			
			if( x >= min(a.mass[i%n1] , a.mass[(i+2)%n1])  && 
				x <= max(a.mass[i%n1] , a.mass[(i+2)%n1]) &&
				y >= min(a.mass[(i+1)%n1] , a.mass[(i+3)%n1]) && 
				y <= max(a.mass[(i+1)%n1] , a.mass[(i+3)%n1]) )
				{
					listRes[k] = x;
					listRes[k+1] = y;
					k = k + 2;
				}
		}
	}
	
	return Point(listRes, n3);
}



void Point::toFile(){
	FILE *f;
	printf("enter name file: ");
	cin >> nameOfFile;

	f = fopen(nameOfFile.c_str(), "w");
	for(int i = 0; i < len; i+=2){
		fprintf(f, "%lf %lf\n", mass[i], mass[i + 1]);
	}
	fclose(f);
}


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
	
