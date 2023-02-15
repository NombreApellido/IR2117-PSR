#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char** argv)
{
    double m = 0, s=0;
    int n=0, element;
    vector<int> elements;
    cin >> element;
    while (not cin.eof())
    {
    	elements.push_back(element);
    	n += 1;
    	cin >> element;
    }	
    for (int i=0; i<n; i++)
    {
    	s += elements[i];
    }
    m = s/n;
    cout << "Arithmetic mean: " << m << endl;
    
    return 0;
}
