#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <cstdio>
using namespace std;
struct Triangle
{
    int t[3];
    bool avaible;
    pair<double, double> pkt; //reprezentant
    bool styczny(Triangle a)
    {
        int licznik=0;
        for(int i=0; i<3; i++)
            for(int j=0; j<3; j++)
                if(a.t[i]==t[j])licznik++;
        if(licznik>=2)return true;
        return false;
    }
};
struct comp
{
    bool operator() (pair<double,int> a, pair<double,int> b)
    {
        return a.first>b.first;
    }
};
int main(int argc, char** argv)
{
    srand(time(0));
    int n, sizeT, a, hard=5;
    if(argc==2)hard=atoi(argv[1]);
    cin>>n;
    vector < pair<double, double> > V(n);
	vector <vector<int> > T(n);
	vector <Triangle> Tr;
	Triangle tr;
	for(int i=0; i<n; i++)
    {
        cin>>V[i].first>>V[i].second>>sizeT;
        for(int j=0; j<sizeT; j++)
        {
            cin>>a;
            T[i].push_back(a);
            if(i>=2 && T[i][j]<i && j>0 && (T[i][j]!=i-1 || i==2))
            {
                 tr.pkt=make_pair((V[i].first+V[T[i][j]].first+V[T[i][j-1]].first)/3.0, (V[i].second+V[T[i][j]].second+V[T[i][j-1]].second)/3.0);
                 tr.t[0]=i;
                 tr.t[1]=T[i][j];
                 tr.t[2]=T[i][j-1];
                 if(rand()%hard==0 && tr.t[0]>2 && tr.t[0]<n-2)tr.avaible=false;
                 else tr.avaible=true;
                 Tr.push_back(tr);
            }
        }
    }
    vector <vector<int> >Graf(Tr.size());
    for(int i=0; i<Tr.size(); i++)
        for(int j=0; j<Tr.size(); j++)
            if(i!=j && Tr[i].styczny(Tr[j]) && Tr[i].avaible && Tr[j].avaible)Graf[i].push_back(j);
    //-----------------------
    int m=Graf.size();
    vector <double> Droga(m,1000000.0);
    vector <int> Mod(m,-1), Path;
    vector <bool> Odw(m, false);
    priority_queue < pair<double,int>, vector< pair<double,int> >, comp > Q;
    double czasStart = clock();
    Droga[0]=0.0;
    Q.push(make_pair(0.0,Droga[0]));
    while(!Q.empty())
    {
        int qt=Q.top().second;
        Odw[qt]=true;
        Q.pop();
        for(int i=0; i<Graf[qt].size(); i++)if(!Odw[Graf[qt][i]])
        {
            double a=(Tr[qt].pkt.first-Tr[Graf[qt][i]].pkt.first), b=(Tr[qt].pkt.second-Tr[Graf[qt][i]].pkt.second), odl=sqrt(a*a+b*b);
            if(Droga[Graf[qt][i]]>Droga[qt]+odl)
            {
                Mod[Graf[qt][i]]=qt;
                Droga[Graf[qt][i]]=Droga[qt]+odl;
            }
            Q.push(make_pair(Droga[qt], Graf[qt][i]));
        }
    }
    int ostatni=rand()%(Tr.size()-2)+1;
    Tr[ostatni].avaible=true;
    int cel=ostatni;
    while(cel>0)
    {
        Path.push_back(cel);
        cel=Mod[cel];
    }
    Path.push_back(0);
    double czasStop = clock();
    //-----------------------
    cout<<n<<endl;
	for(int i=0; i<n; i++)
    {
        cout<<V[i].first<<" "<<V[i].second<<" "<<T[i].size()<<" ";
        for(int j=0; j<T[i].size(); j++)
            cout<<T[i][j]<<" ";
        cout<<endl;
    }
    cout<<Tr.size()<<endl;
    for(int i=0; i<Tr.size(); i++)
    {
        cout<<" "<<Tr[i].pkt.first<<" "<< Tr[i].pkt.second<<" "<<Graf[i].size()<<" ";
        for(int j=0; j<Graf[i].size(); j++)
            cout<<Graf[i][j]<<" ";
        cout<<endl;
    }
    for(int i=0; i<Tr.size(); i++)
        cout<<Tr[i].avaible<<" "<<Tr[i].t[0]<<" "<<Tr[i].t[1]<<" "<<Tr[i].t[2]<<endl;
    if(Path.size()==2 && !Tr[0].styczny(Tr[Tr.size()-3]))Path.resize(1);
    cout<<Path.size()<<endl;
    for(int i=0; i<Path.size(); i++)
        cout<<Path[i]<<" ";
	return 0;
}
