#include <iostream>     // std::cout
#include <algorithm>    // std::random_shuffle
#include <vector>       // std::vector
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
#include <fstream>
#include <list>
#include <stack>
#include <cstdlib>
#include <string>
#include <iomanip>

using namespace std;

typedef pair< int, int > pair_i;
typedef list< pair_i >  list_pairi;
typedef vector< list_pairi > list_listpairi;
ofstream file2;
	
// random generator function:
class Graph
{
	public:
		Graph(int x, double z, string filename)
		{
			srand (unsigned ( time(0) ) * unsigned ( time(0) ) );
			for (int i=0; i < x; ++i) 
		  	{
		  		pair_i p = make_pair(i, 0);
		  		list_pairi  li (1, p);
		  		myvector.push_back(li);
		  	}
		  	random_shuffle ( myvector.begin(), myvector.end() );
		  	int int1 = 0;
		  	for (list_listpairi::iterator it1 = myvector.begin(); it1 != myvector.end(); ++it1)
			{
				for (list_pairi::iterator it = it1->begin(); it != it1->end(); ++it)
				it->second = int1;
				int1++;
			}
			file.open(filename.c_str(), fstream::out);	
		  	myvectorT = myvector;
		  	V = x;
		  	NSCC=0;
		  	si = myvector.size();
		  	q = z;
		  	count = 0;
		  	count2 = 0;
		  	V_S = 0;
		  	E_S = 0;
		  	visited = new bool[V];
		  	cleanVisitRecord();
		  	makeGraph();
		  	printGraph();
		  	file<<endl;
		  	file <<"c : printing all SSCs"<<endl;
		  	file<<endl;
		  	SCC();
		  	file <<"c : number of Strongly connected components is "<<NSCC<<endl;
		  	file2 << setw(7) << V<<setw(7)<<q<<setw(7)<<count<<setw(7)<<count2<<setw(7)<<NSCC<<setw(7)<<V_S<<setw(7)<<E_S<<setw(7)<<V_S2<<setw(7)<<E_S2<<endl;
		  	V_S = E_S = 0;
		  	V_S2 = E_S2 = 0;
		}
		void DFS(int n)
		{
			visited[n] = true;
			list_listpairi::iterator it1 = myvector.begin();
			it1+=n;
			for (list_pairi::iterator it = it1->begin(); it != it1->end(); ++it)	
			{
				if(!visited[it->second])
				{
					DFS(it->second);
				}
			}
			Stack.push(n);
		}
		pair_i DFST(int n, pair_i p1)
		{
			visited[n] = true;
			list_listpairi::iterator it1 = myvectorT.begin();
			it1+=n;
			file << (it1->begin())->first<<" ";
			(p1.first)++;
			for (list_pairi::iterator it = it1->begin(); it != it1->end(); ++it)
			{
				if(!visited[it->second])
				{
					(p1.second)++;
					p1 = DFST(it->second, p1);
				}
				
			}
			return p1;
		}
		void SCC()
		{
			for (int i = 0; i < V; i++) 
			{
				if (!visited[i])
					DFS(i);
			}
			pair_i p1 = make_pair(0, 0);
			//int c = 0, d = 0;
			cleanVisitRecord();
			while (!Stack.empty())
			{
				if (!visited[Stack.top()])
				{
					p1 = DFST(Stack.top(), p1);
					cout<<p1.first<<" "<<p1.second<<endl;
					file <<endl;	
					NSCC++;
					if(V_S < p1.first || E_S < p1.second) 
					{
						V_S2 = V_S;
						E_S2 = E_S;
						V_S = p1.first;
						E_S = p1.second;
					}
					p1 = make_pair(0,0);
				}
				Stack.pop();
			}
		}
		void cleanVisitRecord()
		{
			for(int i = 0; i < V; i++)
				visited[i] = false;
		}
		void printGraph()
		{
			file<<"c : The Graph"<<endl;
			for (list_listpairi::iterator it1 = myvector.begin(); it1 != myvector.end(); ++it1)
			{
				for (list_pairi::iterator it = it1->begin(); it != it1->end(); ++it)
					file << "( "<< it->first << ", "<<it->second<<" )"<<" ";		
				file<<endl;
			}
			file << "c: The Transpose of the Graph"<<endl;
			for (list_listpairi::iterator it1 = myvectorT.begin();  it1 != myvectorT.end(); ++it1)
			{
				for (list_pairi::iterator it = it1->begin(); it != it1->end(); ++it)
					file << "( "<< it->first << ", "<<it->second<<" )"<<" ";
				file<<endl;
			}
		}
	private:
		ofstream file;
		int NSCC;
		int V_S;
		int E_S;
		int E_S2;
		int V_S2;
		int V;
		list_listpairi myvector;
		list_listpairi myvectorT;
		int si;
		double q;
		string filename;
		int count;
		int count2;
		stack<int> Stack;
		bool *visited;
		void makeGraph()
		{
			srand (unsigned ( time(0) ) * unsigned ( time(0) ) );
			for (size_t i = 0; i < si; ++i) 
			{
				for(size_t i1 = i+1; i1 < si; ++i1)
				{
				    if(((double) rand()/RAND_MAX) < q)
						{
							myvector[i1].push_back(myvector[i].front());
							myvectorT[i].push_back(myvectorT[i1].front());
							pair_i it = myvector[i1].front();
							pair_i it2 = myvector[i].front();
							file<<"e "<<it.first<<" "<<it2.second<<endl;
							count2++;
							
						}
						else
						{
							myvector[i].push_back(myvector[i1].front());
							myvectorT[i1].push_back(myvectorT[i].front());
							pair_i it = myvector[i].front();
							pair_i it2 = myvector[i1].front();
							file<<"e "<<it.first<<" "<<it2.second<<endl;
							count++;        
}
					
				}
			}
			file << endl << "Number of forward edges is "<< count <<endl;
			file << endl << "Number of backward edges is "<<count2 <<endl;
		}	
};

int main () 
{
	file2.open("g.txt", fstream::out);
	file2 << setw(7) << "V"<<setw(7)<<"q"<<setw(7)<<"F E"<<setw(7)<<"B E"<<setw(7)<<"SCC"<<setw(7)<<"V S"<<setw(7)<<"E S"<<setw(7)<<"V S 2"<<setw(7)<<"E S 2"<<endl;
	cout<<endl<<endl<<"1000_0D001"<<endl;
	Graph g(1000, 0.001, "1000_0D001.txt");
	cout<<endl<<endl<<"1000_0D005"<<endl;
	Graph g1(1000, 0.005, "1000_0D005.txt");
	cout<<endl<<endl<<"1000_0D01"<<endl;
	Graph g2(1000, 0.01, "1000_0D01.txt");
	cout<<endl<<endl<<"1000_0D02"<<endl;
	Graph g3(1000, 0.02,"1000_0D02.txt");
	cout<<endl<<endl<<"1000_0D05"<<endl;
	Graph g4(1000, 0.05,"1000_0D05.txt");
	cout<<endl<<endl<<"1000_0D1"<<endl;
	Graph g5(1000, 0.1,"1000_0D1.txt");
	cout<<endl<<endl<<"400_0D001"<<endl;
	Graph g10(400, 0.001, "400_0D001.txt");
	cout<<endl<<endl<<"400_0D005"<<endl;
	Graph g11(400, 0.005, "400_0D005.txt");
	cout<<endl<<endl<<"400_0D01"<<endl;
	Graph g12(400, 0.01, "400_0D01.txt");
	cout<<endl<<endl<<"400_0D02"<<endl;
	Graph g13(400, 0.02,"400_0D02.txt");
	cout<<endl<<endl<<"400_0D05"<<endl;
	Graph g14(400, 0.05,"400_0D05.txt");
	cout<<endl<<endl<<"400_0D1"<<endl;
	Graph g15(400, 0.1,"400_0D1.txt");
	file2<<endl<<endl;
	return 0;
}
