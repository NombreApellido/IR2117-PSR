#include <iostream>
#include <cmath>
using namespace std;
int main()
{
    double a, b, c, x1, x2, dis1, dis2;
    cout << "Enter a: ";
    cin >> a;
    cout << "Enter b: ";
    cin >> b;
    cout << "Enter c: ";
    cin >> c;
    if (b*b-4*a*c < 0)
    {
        x1 = -b/(2*a);
        x2 = -b/(2*a);
        dis1 = sqrt(-1*(b*b-4*a*c))/(2*a);
        dis2 = sqrt(-1*(b*b-4*a*c))/(2*a);
        if (dis1 > 0)
        {
        cout << "x2 = " << x2 << "-"<< dis2 << "i"<< endl;
        cout << "x1 = " << x1 << "+"<< dis1 << "i" << endl;  
        }
        else
        {
        cout << "x1 = " << x1 << "-" << dis1 << "i"<< endl;
        cout << "x2 = " << x2 << "+"<< dis2 << "i" << endl;  
        }
    }
    if(b*b-4*a*c == 0)
    {
        x1 = (-b+sqrt(b*b-4*a*c))/(2*a);
        cout << "x = " << x1 << endl;
    }
    if(b*b-4*a*c > 0)
    {
        x1 = (-b+sqrt(b*b-4*a*c))/(2*a);
        x2= (-b-sqrt(b*b-4*a*c))/(2*a);
        cout << "x1 = " << x1 << endl;
        cout << "x2 = " << x2 << endl;
  
    }
    
    return 0;
}

