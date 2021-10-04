#include "Point.h"


int main(void){
    int n, i;
    double *list, *list1;


    cin >> n;
    cout << "n ==" << n << endl;
    list = new double[n];
    if(n % 2 != 0){
        n += 1;
    }
    for(i = 0; i < n; i++){
        cout << "enter x = " ;
        cin >> list[i];
    }
    
    Point a(list, n);
    a.Print();
    // a.toFile();
    // a.Draw();
    // cout << endl;

    n = 0;
    cin >> n;
    cout << "n ==" << n << endl;
    if(n % 2 != 0){
        n += 1;
    }
    list1 = new double[n];
    for(i = 0; i < n; i++){
        cout << "enter x = " ;
        cin >> list1[i];

    }
    Point b(list1, n);
    b.Print();
    


    
    Point c;
    c = b - a;
    c.Print();

    // Point c(list, n);
    // c.Print();
    // c.toFile();
    // c.DrawDot();
    // c.DrawLines();
    
    return 0;
}