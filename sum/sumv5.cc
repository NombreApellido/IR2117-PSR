#include <iostream>


using namespace std;
int sumv3(int a){
    int sum=0;
    for(int i = 1; i <= a; i=i+1){
        sum = sum + i;
    }
    return sum;
}
int main()
{
   

    cout<<"Enter a number: ";
    int a;
    cin >> a;
    if (a>=1)
    {
        int sum;
        sum = sumv3(a);
        cout<<"The sum from 1 to "<< a<<" is "<< sum << endl;
    }
    else{
    	while(a<1)
    	{
        	cout<<"Introduce a number higher or equal to 1: "<<endl;
        	cin>>a;
        }
                cout<<"The sum from 1 to "<< a<<" is "<< sum << endl;
    }
    return 0;
}
