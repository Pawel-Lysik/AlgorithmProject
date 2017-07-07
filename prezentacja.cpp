#include <iostream>
#include <vector>
#include <fstream>
#include <utility>
#include <cstdlib>
struct Triangle
{
    int t[3];
    bool avaible;
};
using namespace std;
int main(int argc, char** argv)
{
    int n, sizeT, a;
    cin>>n;
    vector < pair<double, double> > V(n);
	vector <vector<int> > T(n);
	vector <Triangle> Pola;
	for(int i=0; i<n; i++)
    {
        cin>>V[i].first>>V[i].second>>sizeT;
        for(int j=0; j<sizeT; j++)
        {
            cin>>a;
            T[i].push_back(a);
        }
    }
    vector < pair<double, double> > P; //punkty w trójk¹tach
    vector <vector<int> > Graf;
    vector <int> Path;
    int sizeP, sizeGraf, sizePath;
    if(argc==1 || atoi(argv[1])>0)
    {
        cin>>sizeP;
        P.resize(sizeP);
        Graf.resize(sizeP);
        Pola.resize(sizeP);
        for(int i=0; i<sizeP; i++)
        {
            cin>>P[i].first>>P[i].second>>sizeGraf;
            for(int j=0; j<sizeGraf; j++)
            {
                cin>>a;
                Graf[i].push_back(a);
            }
        }
        for(int i=0; i<sizeP; i++)
            cin>>Pola[i].avaible>>Pola[i].t[0]>>Pola[i].t[1]>>Pola[i].t[2];
        cin>>sizePath;
        Path.resize(sizePath);
        for(int i=0; i<sizePath; i++)
            cin>>Path[i];
    }
	int poz_x=400, poz_y=100, circle_size=2;
	ofstream myfile("output.html");
	myfile << "<!DOCTYPE html>\n <html>\n <body>\n <svg width=\"1800\" height=\"1000\" > \n";
	for (int i = 0; i<n; i++)
	{
	    cout<<i<<": ";
		for (int j = 0; j < T[i].size(); j++)
		{
		    if(argc==1 || atoi(argv[1])>1)
            {
                myfile<<"<line x1=\""<<V[i].first*10 + poz_x<<"\" y1=\""<<V[i].second*10 + poz_y<< "\" x2=\""<<
                V[T[i][j]].first*10 + poz_x<<"\" y2=\""<<V[T[i][j]].second*10 + poz_y<<"\" style=\"stroke:rgb(10,50,10); stroke-width:1\" /> \n";
                myfile<<"<circle cx=\""<<V[i].first*10 + poz_x<<"\" cy=\""<<V[i].second*10 + poz_y<<
                "\" r=\""<<circle_size<<"\" stroke=rgb(10,"<<250-i*250/n/2<<",10) stroke-width=\"4\" fill=\"green\" /> \n";
                cout<<T[i][j]<<" ";
            }
		}
		cout<<endl;
	}
	if(argc==1 || atoi(argv[1])>0)
    {
        for (int i = 0; i<sizeP; i++)
        {
            if(!Pola[i].avaible)//przeszkody
                myfile<<"<polygon points=\""<<V[Pola[i].t[0]].first*10 + poz_x<<","<<V[Pola[i].t[0]].second*10 + poz_y<<" "<<V[Pola[i].t[1]].first*10 + poz_x<<","<<
                V[Pola[i].t[1]].second*10 + poz_y<<" "<<V[Pola[i].t[2]].first*10 + poz_x<<","<<V[Pola[i].t[2]].second*10 + poz_y<<"\""<<"style=\"fill:lime;stroke:purple;stroke-width:1\" /> \n";
            if(argc==1 || atoi(argv[1])>1)
            {
                //reprezentanci
                myfile<<"<circle cx=\""<<P[i].first*10 + poz_x<<"\" cy=\""<<P[i].second*10 + poz_y<<"\" r=\""<<circle_size<<
                "\" stroke=rgb("<<250-i*250/sizeP/2<<",10,10) stroke-width=\"5\" fill=\"red\" /> \n";
                //graf dla Dijkstry
                for(int j=0; j<Graf[i].size(); j++)
                    myfile<<"<line x1=\""<<P[i].first*10 + poz_x<<"\" y1=\""<<P[i].second*10 + poz_y<<
                    "\" x2=\""<<P[Graf[i][j]].first*10 + poz_x<<"\" y2=\""<<P[Graf[i][j]].second*10 + poz_y<<"\" style=\"stroke:rgb(200,10,10); stroke-width:1\" /> \n";
            }
        }
        //najkrotsza sciezka
        for (int i = 0; i<Path.size(); i++)
        {
            myfile<<"<circle cx=\""<<P[Path[i]].first*10 + poz_x<<"\" cy=\""<<P[Path[i]].second*10 + poz_y<<
            "\" r=\""<<circle_size<<"\" stroke=rgb("<<250-i*250/sizePath/2<<","<<250-i*250/sizePath/2<<",10) stroke-width=\"5\" fill=\"yellow\" /> \n";
            if(i>0)
                myfile<<"<line x1=\""<<P[Path[i-1]].first*10 + poz_x<<"\" y1=\""<<P[Path[i-1]].second*10 + poz_y<<
                "\" x2=\""<<P[Path[i]].first*10 + poz_x<<"\" y2=\""<<P[Path[i]].second*10 + poz_y<<"\" style=\"stroke:rgb(200,200,10); stroke-width:2\" /> \n";
        }
        myfile<<"<circle cx=\""<<P[0].first*10 + poz_x<<"\" cy=\""<<P[0].second*10 + poz_y<<
            "\" r=\""<<circle_size<<"\" stroke=\"yellow\" stroke-width=\"5\" fill=\"yellow\" /> \n";
    }
	myfile<<"</svg>\n </body>\n </html>\n";
	myfile.close();
	return 0;
}
