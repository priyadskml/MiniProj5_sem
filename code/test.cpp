#include <iostream>     // std::cout
#include <algorithm>    // std::random_shuffle
#include <vector>       // std::vector
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
#include <fstream>
#include <list>
//#include <string>
#include <stack>
using namespace std;

// random generator function:
class Graph
{
	public:
	
		Graph(int x, double y, double z)
		{
			srand ( unsigned ( time(0) ) );
			for (int i=1; i < x+1; ++i) 
		  	{
		  		list<int> li (1, i);
		  		myvector.push_back(li);
		  	}
		  	random_shuffle ( myvector.begin(), myvector.end() );
		  	myvectorT = myvector;
		  	V= x;
		  	si = myvector.size();
		  	p = y;
		  	q = z;
		  	makeGraph();
		  	//printGraph();
		  	cout <<"printing all SSCs"<<endl;
		  	printSCCs();
		}
		void printGraph()
		{
			cout<<"The Graph"<<endl;
			for (size_t i = 0; i < si; ++i) 
			{
			  	list<int>::iterator li;
			  	for (li = myvector[i].begin(); li != myvector[i].end(); ++li)
					std::cout << *li << " ";
				cout<<endl;
				cout<<endl;
			}
			cout<<"The Transpose of the Graph"<<endl;
			for (size_t i = 0; i < si; ++i) 
			{
			  	list<int>::iterator li;
			  	for (li = myvectorT[i].begin(); li != myvectorT[i].end(); ++li)
					std::cout << *li << " ";
				cout<<endl;
			}
		}
		
		void DFSUtil(int v, bool visited[])
		{
			// Mark the current node as visited and print it
			visited[v] = true;
			//cout<<"Hi1"<<endl;
			cout << myvector[v].front() << " ";
		 
			// Recur for all the vertices adjacent to this vertex
			list<int>::iterator i;
			for (i = myvector[v].begin(); i != myvector[v].end(); ++i)
				if (!visited[*i]&& *i!=V)
				    DFSUtil(*i, visited);
		}
		void DFSTransposeUtil(int v, bool visited[])
		{
			// Mark the current node as visited and print it
			visited[v] = true;
			cout << myvectorT[v].front() << " ";
		 
			// Recur for all the vertices adjacent to this vertex
			list<int>::iterator i;
			for (i = myvectorT[v].begin(); i != myvectorT[v].end(); ++i)
				if (!visited[*i] && *i!=V)
				    DFSUtil(*i, visited);
		}
		void fillOrder(int v, bool visited[], stack<int> &Stack)
		{
			// Mark the current node as visited and print it
			visited[v] = true;
		 	//cout<<"Hi5"<<endl;
			// Recur for all the vertices adjacent to this vertex
			list<int>::iterator i;
			for(i = myvector[v].begin(); i != myvector[v].end(); ++i)
			{
				//cout<<*i<<endl;
				if(!visited[*i] && *i != V)
				    fillOrder(*i, visited, Stack);
				//cout<<*i<<endl;
			}
		 //cout<<"Hi6"<<endl;
			// All vertices reachable from v are processed by now, push v 
			Stack.push(v);
		}
 void printSCCs()
		{
			for(int i = 0; i < V; i++)
			visited[i] = false;
			for(int i = 0; i < V; i++)
			if(visited[i] == false)
			    fillOrder(i, visited, Stack);
				    
		}
		void fillOrder(int v, bool visited[], stack<int> &Stack)
		{
			// Mark the current node as visited and print it
			visited[v] = true;
		 
			// Recur for all the vertices adjacent to this vertex
			list<int>::iterator i;
			for(i = adj[v].begin(); i != adj[v].end(); ++i)
				if(!visited[*i])
				    fillOrder(*i, visited, Stack);
		 
			// All vertices reachable from v are processed by now, push v 
			Stack.push(v);
		}
		void Graph::DFSUtil(list < int > v, vector < list < int > > v1)
		{
			// Mark the current node as visited and print it
			visited[v] = true;
			cout << v << " ";
		 
			// Recur for all the vertices adjacent to this vertex
			list<int>::iterator i;
			for (i = adj[v].begin(); i != adj[v].end(); ++i)
				if (!visited[*i])
				    DFSUtil(*i, visited);
		}
// The main function that finds and prints all strongly connected 
// components
		void printSCCs()
		{
			stack<int> Stack;
		 	//cout<<"Hi2"<<endl;
			// Mark all the vertices as not visited (For first DFS)
			bool *visited = new bool[V];
			for(int i = 0; i < V; i++)
				visited[i] = false;
		 	//cout<<"Hi3"<<endl;
			// Fill vertices in stack according to their finishing times
			for(int i = 0; i < V; i++)
				if(visited[i] == false)
				    fillOrder(i, visited, Stack);
		 	//cout<<"Hi4"<<endl;
			// Create a reversed graph
			//Graph gr = getTranspose();
		 
			// Mark all the vertices as not visited (For second DFS)
			//cout<<"Hi1"<<endl;
			for(int i = 0; i < V; i++)
				visited[i] = false;
		 
			// Now process all vertices in order defined by Stack
			while (Stack.empty() == false)
			{
				// Pop a vertex from stack
				int v = Stack.top();
				Stack.pop();
		 
				// Print Strongly connected component of the popped vertex
				if (visited[v] == false)
				{
				    DFSTransposeUtil(v, visited);
				    cout << endl<<endl<<endl<<endl;
				}
			}
		}
	private:
		int V = 0;
		vector< list < int > > myvector;
		vector< list < int > > myvectorT;
		int si = 0;
		double p = 0, q = 0;
		string filename;
		int count = 0;
		int count2 = 0;
		void makeGraph()
		{
			srand ( unsigned ( time(0) ) );
			for (size_t i = 0; i < si; ++i) 
			{
				for(size_t i1 = i+1; i1 < si; ++i1)
				{
				    if(((double) rand()/RAND_MAX) < p)
					{
						if(((double) rand()/RAND_MAX) < q)
						{
							myvector[i1].push_back(myvector[i].front());
							myvectorT[i].push_back(myvectorT[i1].front());
							//file<<"e "<<myvector[i1].front()<<" "<<myvector[i].front()<<endl;
							count2++;
							count--;
						}
						else
						{
							myvector[i].push_back(myvector[i1].front());
							myvectorT[i1].push_back(myvectorT[i].front());
							//file<<"e "<<myvector[i].front()<<" "<<myvector[i1].front()<<endl;
						}
						count++;        
					}
				}
			}	
		}	
};
int main () 
{
  	/*srand ( unsigned ( time(0) ) );
  	vector< list < int > > myvector;
	ofstream file;
	file.open("graph.txt", fstream::out);
	file<<"c Generating Graph for feedback arc set problem"<<endl;
  // set some values:
  	for (int i=1; i<1000; ++i) 
  	{
  		list<int> li (1, i);
  		myvector.push_back(li); 
  	}

  // using built-in random generator:
  	random_shuffle ( myvector.begin(), myvector.end() );
  	int si = myvector.size();
  	for (size_t i = 0; i < si; ++i) 
    {
      	list<int>::iterator li;
       	for (li = myvector[i].begin(); li != myvector[i].end(); ++li)
            std::cout << *li << " ";
        cout<<endl;
    }
	int count = 0;
	int count2 = 0;
	
	for (size_t i = 0; i < si; ++i) 
	{
		for(size_t i1 = i+1; i1 < si; ++i1)
		{
            if(((double) rand()/RAND_MAX) < 0.01)
			{
				if(((double) rand()/RAND_MAX) < 0.02)
				{
					myvector[i1].push_back(myvector[i].front());
					file<<"e "<<myvector[i1].front()<<" "<<myvector[i].front()<<endl;
					count2++;
					count--;
				}
				else
				{
					myvector[i].push_back(myvector[i1].front());
					file<<"e "<<myvector[i].front()<<" "<<myvector[i1].front()<<endl;
				}
				count++;        
		    }
		}
	}
    for (size_t i = 0; i < si; ++i) 
    {
      	list<int>::iterator li;
      	for (li = myvector[i].begin(); li != myvector[i].end(); ++li)
    	    std::cout << *li << " ";
        cout<<endl;
    }
	cout << count <<endl <<count2 <<endl;
	file.close();*/
	Graph g(1000, 0.01, 0.02);
	return 0;
}
