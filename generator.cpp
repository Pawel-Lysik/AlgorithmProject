#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#define last figura[figura.size()-1]
using namespace std;
int main(int argc, char** argv)
{
	srand(time(0));
	int n, suma=0;
	if(argc==1)n=rand()%20+5;
	else n=atoi(argv[1]);
	cout<<n+4<<endl;
	for(int i=0; i<n; i++)
        cout<<(double)rand()/RAND_MAX*120<<" "<<(double)rand()/RAND_MAX*80<<endl;
    cout<<0.0<<" "<<0.0<<endl<<0.0<<" "<<80.0<<endl<<120.0<<" "<<0.0<<endl<<120.0<<" "<<80.0<<endl;
	return 0;
}
