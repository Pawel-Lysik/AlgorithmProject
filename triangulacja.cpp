#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include <algorithm>
#include <ctime>
#include <cstdio>
using namespace std;
bool f(pair<double, double> a, pair <double, double> b)
{
	if (a.first<b.first)return true;
	if (a.first>b.first)return false;
	if (a.second<b.second)return true;
	return false;
}
double sinus(pair <double, double> nowy, pair <double, double> stary)
{
    double ax=stary.first, ay=stary.second, bx=ax, by=nowy.second, cx=nowy.first, cy=nowy.second;
	double b = sqrt((ax - cx)*(ax - cx) + (ay - cy)*(ay - cy));
	double a = cy-ay;
	return a/b;
}
int main()
{
    double czasZero = clock();
	int n;
	cin >> n;
	vector < pair<double, double> > V(n);
	vector < pair<int, int> > O(n);
	vector <vector<int> > T(n);
	for (int i = 0; i<n; i++)
        cin >> V[i].first >> V[i].second;
	sort(V.begin(), V.end(), f);
	double czasStart = clock();
	int last;
    double sinkata, horizon;
	for (int i = 0; i<3; i++)
	{
		for (int j = 0; j<3; j++)
            if (j != i)T[i].push_back(j);
        if( sinus(V[(i+1)%3],V[i]) > sinus(V[(i+2)%3],V[i]) )
        {
            O[i].first=(i+1)%3;
            O[i].second=(i+2)%3;
        }
        else
        {
            O[i].first=(i+2)%3;
            O[i].second=(i+1)%3;
        }
	}
	for (int i = 3; i<n; i++)
	{
		last=i-1;
		sinkata = sinus(V[last], V[i]);
		horizon = sinkata;
		while (horizon <= sinkata+0.001)
		{
			horizon=sinkata;
			T[i].push_back(last);
			T[last].push_back(i);
			O[i].first = last;
            last = O[last].first;
            if(last==i)break;
            if(sinkata>0.999)break;
			sinkata = sinus(V[last], V[i]);
		}
		last=i-1;
		sinkata = sinus(V[last], V[i]);
		horizon = sinkata;
		while (horizon >= sinkata-0.001)
		{
			horizon = sinkata;
			T[i].push_back(last);
			T[last].push_back(i);
            O[i].second = last;
            last = O[last].second;
            if(last==i)break;
            if(sinkata<-0.999)break;
			sinkata = sinus(V[last], V[i]);
		}
	}
	double czasStop = clock();
	cout<<n<<endl;
	int sizeT=0;
	for(int i=0; i<n; i++)
    {
        cout<<V[i].first<<" "<<V[i].second<<" "<<T[i].size()<<" ";
        for(int j=0; j<T[i].size(); j++)
            cout<<T[i][j]<<" ";
        cout<<endl;
        sizeT+=T[i].size();
    }
    //cout<<"l.krawedzi:"<<sizeT/2<<endl;
    //printf("Algorytm %fsek.\n", ((czasStop-czasStart)/CLOCKS_PER_SEC ) );
    //printf("Program %fsek.\n", ((czasStop-czasZero)/CLOCKS_PER_SEC ) );
	return 0;
}
