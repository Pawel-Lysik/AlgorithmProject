#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <cmath>
#include <ctime>
#include <cstdlib>
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
struct Vertex
{
    int id, prev;
    bool odw;
    double dist, tentative;
    Vertex(int i, double d, double t)
    {
        id=i; dist=d; tentative=t; prev=-1; odw=false;
    }
    Vertex(){}
    cpy(Vertex &v)
    {
        id=v.id; prev=v.prev; odw=v.odw; dist=v.dist; tentative=v.tentative;
    }
};
struct comp
{
    bool operator() (Vertex a, Vertex b)
    {
        return a.dist+a.tentative>b.dist+b.tentative;
    }
};
inline double dist(double x1, double y1, double x2, double y2)
{
    double a=(x1-x2), b=(y1-y2);
    return sqrt(a*a+b*b);
}
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
	for(int i=0; i<n; i++)//tworzenie reprezentantów
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
    int cel=rand()%(Tr.size()-2)+1;
    Tr[cel].avaible=true;
    vector <Vertex> Vrtx(Graf.size());
    for(int i=0; i<Graf.size(); i++)
    {
        Vertex v(i, 1000000.0, dist(V[i].first, V[i].second, V[cel].first, V[cel].second));
        Vrtx[i].cpy(v);
    }
    priority_queue <Vertex, vector<Vertex>, comp > Q;
    Vrtx[0].dist=0;
    Q.push(Vrtx[0]);
    while(!Q.empty())
    {
        int qt=Q.top().id;
        if(qt==cel)break;
        Vrtx[qt].odw=true;
        Q.pop();
        for(int i=0; i<Graf[qt].size(); i++)if(!Vrtx[Graf[qt][i]].odw)
        {
            double odl=dist(Tr[qt].pkt.first, Tr[qt].pkt.second, Tr[Graf[qt][i]].pkt.first, Tr[Graf[qt][i]].pkt.second);
            if(Vrtx[Graf[qt][i]].dist>Vrtx[qt].dist+odl)
            {
                Vrtx[Graf[qt][i]].prev=qt;
                Vrtx[Graf[qt][i]].dist=Vrtx[qt].dist+odl;
            }
            Vertex v(Graf[qt][i], Vrtx[Graf[qt][i]].dist, dist(V[qt].first, V[qt].second, V[cel].first, V[cel].second));
            Q.push(v);
        }
    }
    vector <int> Path;
    while(cel>0)
    {
        Path.push_back(cel);
        cel=Vrtx[cel].prev;
    }
    Path.push_back(0);
    //-----------------------
    {//tworzenie wyjœcia
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
    }
	return 0;
}
