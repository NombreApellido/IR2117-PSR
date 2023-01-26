#include <iostream>

using namespace std;

int main()
{
    cout<<"Enter a number: ";
    int a;
    int sum=0;
    cin >> a;
    for(int i = 1; i <= a; i=i+1){
        sum = sum + i;
    }
    cout<<"The sum from 1 to "<< a<<" is "<< sum << endl;

    return 0;
}


