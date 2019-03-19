#include <fstream>
#include <string>
#include <iostream>
using namespace std;
int main() 
{ 
    ifstream file("Read.txt");
    string str; 
    while (std::getline(file, str))
    {
        cout<<str<<endl;
    }
}