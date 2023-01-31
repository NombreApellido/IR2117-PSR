#include <iostream>

using namespace std;

int main()
{

    int a, b;
    int sum = 0;
    cout << "Enter a: ";
    cin >> a;
    cout << "Enter b: ";
    cin>> b;
    for(int i = a; i<=b;i++)
    {
        sum += i;
    
    }
    cout << "The sum is " << sum;
    return 0;
}
