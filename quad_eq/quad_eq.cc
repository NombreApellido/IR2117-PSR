#include <iostream>
#include <cmath>
using namespace std;
int main()
{
    double a, b, c, x1, x2;
    cout << "Enter a: ";
    cin >> a;
    cout << "Enter b: ";
    cin >> b;
    cout << "Enter c: ";
    cin >> c;
    if (b*b-4*a*c < 0)
    {
        cout << "Discriminant below 0, try again"   ; 
    }
    if(b*b-4*a*c == 0)
    {
        cout << "x = 0" << endl;
    }
    else
    {
        x1 = (-b+sqrt(b*b-4*a*c))/(2*a);
        x2 = (-b-sqrt(b*b-4*a*c))/(2*a);
        cout << "x1 = " << x1 << endl;
        cout << "x2 = " << x2 << endl;
  
    }
    
    return 0;
}

