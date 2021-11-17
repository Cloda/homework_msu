#include "Point.h" 


Point::Point(){
    m_mass = new double[2];
    m_mass[0] = 0.;
    m_mass[1] = 0.;
    m_len = 2;

}

Point::~Point(){
	delete [] m_mass;
	m_mass = 0;
}

Point::Point(const Point &a){
	int i;
	m_len = a.m_len;
	m_mass = new double[m_len];
	
	for(i = 0; i < m_len; i++){
		m_mass[i] = a.m_mass[i];
	}
	if(toFile()){
		cout << "wrong file" << endl;
	}
}

// конструктор с массивом точек
Point::Point(double *list, int size){
	int i;
	m_len = size;

	m_mass = new double[m_len];
	
	for(i = 0; i < m_len; i++){
		m_mass[i] = list[i];
	}
}

// перегрузка оператора равенства
const Point & Point::operator=(const Point &b){
	int i;
	m_len = b.m_len;
	m_mass = new double[m_len];
	
	for(i = 0; i < m_len; i++){
		m_mass[i] = b.m_mass[i];
	}
	
	if(toFile()){
		cout << "wrong file" << endl;
	}

   	return *this;
}

// перегрузка оператора сравнение 
int operator==(const Point &a, const Point &b){
	int count = 0, flag = 0;
	if(a.m_len == b.m_len){
		for(int i = 0; i < a.m_len - 2; i += 2){
			for(int j = 0; j < b.m_len - 2; j += 2){
				if(a.m_mass[i] == b.m_mass[j] && a.m_mass[i + 1] == b.m_mass[j + 1]){
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

	if (flag == a.m_len - 2){
		return 1;
	} else {
		return 0;
	}
}

// занесение точек в файл
int Point::toFile(){
	int i, count = 0;
	FILE *f;
	cout << "Enter name file: ";
	cin >> m_nameOfFile;
	
	f = fopen(m_nameOfFile.c_str(), "w");
	if(f == NULL){
		return 1;
	}
	
	for(i = 0; i < m_len; i += 2){
		fprintf(f, "%lf %lf\n", m_mass[i], m_mass[i + 1]);
		if((i + 2) % (8*SPLIT + 2) == 0 && i != 0){
			fprintf(f, "\n");
		}
	}
	fclose(f);

	return 0;
}

// отрисовка линий
void Point::DrawLines(){
	if (m_nameOfFile.length() != 0){
		string str = "plot \"" + m_nameOfFile + "\" with lines\n";

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
	if (m_nameOfFile.length() != 0){
		string str = "plot \"" + m_nameOfFile + "\" using 1:2\n";
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