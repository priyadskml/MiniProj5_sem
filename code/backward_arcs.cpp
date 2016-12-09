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


vector < int > v1;
vector < int > v2;
//int n = 5000;
//int G[5000][5000]={0};
//double q = 0.5;
/*typedef list< int >  list_int;
int main()
{
int visited[5000] = {0};
srand (unsigned ( time(0) ) );
for(int x = 0; x < n; x++)
{
	for(int y = x; y < n; y++)
	{
		if(x==y)
		{
			G[x][y] = 0;
		}
		else
		{
			double p = ((double) rand()/RAND_MAX);
			//cout<<p<<endl;
			if(p < q)
			{
				G[y][x] = 1;
				G[x][y] = 0;	
			}
			else
			{
				G[x][y] = 1;
				G[y][x] = 0;
			}
		}
	}		
}
for(int x = 0; x < n; x++)
{
	for(int y = 0; y < n; y++)
	{
		cout<<G[x][y]<<" ";
		}
		cout<<endl;
		}

}
void DFS(int i, int **G, int *V){



}
*/


struct node_info
{
    int no;
    int lv_time, st_time;
}*q = NULL;


struct node
{
    node_info *pt;
    node *next;
}*top = NULL, *p = NULL, *np = NULL;


struct node1
{
    node1 *link;
    node_info *pt1;
}*head = NULL, *m = NULL, *n = NULL, *np1 = NULL;


int c = 0;
void push(node_info *ptr)
{
    np = new node;
    np->pt = ptr;
    np->next = NULL;
    if (top == NULL)
    {
        top = np;
    }
    else
    {
        np->next = top;
        top = np;
    }
}
node_info *pop()
{
    if (top == NULL)
    {
        //cout<<"underflow\n";
    }
    else
    {
        p = top;
        top = top->next;
        return(p->pt);
        delete(p);
    }
}

void store(node_info *ptr1)
{
    np1 = new node1;
    np1->pt1 = ptr1;
    np1->link = NULL;
    if (c == 0)
    {
        head = np1;
        m = head;
        m->link = NULL;
        c++;
    }
    else
    {
        m = head;
        np1->link = m;
        head = np1;
    }
}

void remove(int x)
{
    m = head;
    if ((m->pt1)->no == x)
    {
        head = head->link;
        delete(m);
    }
    else
    {
        while ((m->pt1)->no != x && m->link != NULL)
        {
            n = m;
            m = m->link;
        }
        if ((m->pt1)->no == x)
        {
            n->link = m->link;
            delete(m);
        }
        else if (m->link == NULL)
        {
            //cout<<"error\n";
        }
    }
}            

void topo(int *v, int am[][5000], int i)
{
    q = new node_info;
    q->no = i;
    q->st_time = c;
    push(q);
    v[i] = 1;
    for (int j = 0; j < 5000; j++)
    {
        if (am[i][j] == 0  || (am[i][j] == 1 && v[j] == 1)){
            continue;}
        else if (am[i][j] == 1 && v[j] == 0)
        {
            c++;
            topo(v,am,j);
        }
    }
    c++;
    q = pop();
    q->lv_time = c;
    store(q);
    return;
}

void topo1(int *v, int am[][5000], int i)
{
    v[i] = 1;
    remove(i);
	v2.push_back(i);
    //cout<<i<<endl;
    for (int j = 0; j < 5000; j++)
    {
        if (am[i][j] == 0  || (am[i][j] == 1 && v[j] == 1))
        {
            continue;
        }
        else if (am[i][j] == 1 && v[j] == 0)
        {
            topo1(v,am,j);
        }
    }
    return;
}

int main()
{
    int v[5000], am[5000][5000], amt[5000][5000];
    for (int i = 0; i < 5000; i++)
    {
		v[i] = 0;
	}
	bool nloop = false;
	srand (unsigned ( time(0) ) );
	for(int x = 0; x < 5000; x++)
	{
		for(int y = x; y < 5000; y++)
		{
			if(x==y)
			{
				am[x][y] = 0;
			}
			else
			{
				double p_ = ((double) rand()/RAND_MAX);
				//cout<<p<<endl;
				if(p_ < 0.0001)
				{
					am[y][x] = 1;
					am[x][y] = 0;	
				}
				else
				{
					am[x][y] = 1;
					am[y][x] = 0;
				}
			}
		}		
	}
    topo(v, am, 0);
    for (int i = 0; i < 5000; i++)
    {
        v[i] = 0;
        for (int j = 0; j < 5000; j++)
        {
            amt[j][i] = am[i][j];
        }
    }
    int sccN = 0;
    while (head != NULL)
    {
        //cout<<"Strongly Connected Components:\n";                 
        topo1(v, amt, (head->pt1)->no);
        sccN++;
        if(v1.size()<v2.size()){v1=v2;}
			v2=vector<int>();
    }
    vector< int >::iterator it;
    //cout<<"largest SCC"<<endl;
    int sccL = 0;
    for(it=v1.begin() ; it < v1.end(); it++ ) 
    {
    	sccL++;
    	//cout<<*it<<endl;
    }
    int si = v1.size();
    int *V_1;
    V_1 = new int[si];
    int **A= new int*[si];
    for(int x = 0; x<si;x++)
    	A[x] = new int[si];
    int **R_= new int*[si];
    for(int x = 0; x<si;x++)
    	R_[x] = new int[si];
    int **S_= new int*[si];
    for(int x = 0; x<si;x++)
    	S_[x] = new int[si];
    int **T_= new int*[si];
    for(int x = 0; x<si;x++)
    	T_[x] = new int[si];
    int **U_= new int*[si];
    for(int x = 0; x<si;x++)
    	U_[x] = new int[si];
    int **F_= new int*[si];
    for(int x = 0; x<si;x++)
    	F_[x] = new int[si];
    int **B_= new int*[si];
    for(int x = 0; x<si;x++)
    	B_[x] = new int[si];
    int i_ = 0;	
    int f1 = 0, b1 = 0, f2 = 0, b2 = 0; 
	do
	{
		nloop = false;
		for(int x = 0; x<si; x++)
		{
			V_1[x]=v1.at(x);
		}
		for(int x = 0; x<si; x++)
		{
		for(int y = 0; y<si; y++)
		{
		B_[x][y] = F_[x][y] = R_[x][y] = S_[x][y] = T_[x][y] =U_[x][y] = A[x][y]= 0; 
		}}
		for(int x = 0; x<si; x++)
		{
			for(int y = 0; y<si; y++)
			{
				if(am[V_1[x]][V_1[y]] == 1)
				{
					A[x][y]=1;//cout<<x<<" "<<y<<endl;
				}
				else{
					A[x][y]=0;/*cout<<A[x][y]<<" "<<endl;*/
					}
			}
		//cout<<endl;
		}
		if(i_==0){
		for(int x = 0; x<si; x++)
		{
			for(int y = x+1; y<si; y++)
			{
				if(am[V_1[x]][V_1[y]] == 1)
				{
					f1++;
				}
				else if(am[V_1[y]][V_1[x]] == 1){
					b1++;
					}
			}
		//cout<<endl;
		}
		i_++;
		}
		for(int x = 0; x<si-1;x++)
		{
			if(A[x][x+1]==1) {R_[x][x+1] = 1;U_[x][x+1] = 1;}
			if(A[x+1][x]==1) {S_[x][x+1] = 1;T_[x][x+1] = 1;}
		}
		//cout<<i_<<endl;
		for(int x = 0; x<si-1; x++)
		{
			for(int y=x+2; y<si; y++)
			{
				R_[x][y]=R_[x][y-1]+A[x][y];
				S_[x][y]=S_[x][y-1]+A[y][x];
			}
		}
		 //cout<<i_<<endl;
		for(int x = si-2; x>0; x--)
		{
			for(int y = x+2; y<si; y++)
			{
				T_[x][y]=T_[x+1][y]+A[y][x];
				U_[x][y]=U_[x+1][y]+A[y][x];
			}
		}
		 //cout<<i_<<endl;
		for(int x = 0; x <si; x++){
			F_[0][x]=R_[0][x];
			B_[0][x]=S_[0][x];
		}
		 //cout<<i_<<endl;
		for(int x=2; x<si; x++){
			for(int y = 1; y<x; y++){
			F_[x][y]=F_[x-1][y]+R_[x][y]-U_[0][x];
			B_[x][y]=B_[x-1][y]+S_[x][y]-T_[0][x];
			} 
		}
		 //cout<<i_<<endl;
		v2=vector<int>();
		for(int x = 0; (x<si-1) && !nloop; x++)
			for(int y = x+1; (y<si) && !nloop ; y++){
			//cout<<"loop #"<<x<<" 1"<<endl;
				if(F_[x][y]>B_[x][y]){
					//cout<<"loop #"<<x<<endl;
					nloop = true;
					for(int z= x+1; z<=y; z++)
					v2.push_back(v1.at(z));
					for(int z= 0; z<=x; z++)
					v2.push_back(v1.at(z));
					for(int z= y+1; z<si; z++)
					v2.push_back(v1.at(z));
					v1=v2;
					v2=vector<int>();
				}
			}
			 //cout<<i_<<endl;
	}while(nloop);
	for(int x = 0; x<si; x++)
		{
			for(int y = x+1; y<si; y++)
			{
				if(am[V_1[x]][V_1[y]] == 1)
				{
					f2++;
				}
				else if(am[V_1[y]][V_1[x]] == 1){
					b2++;
					}
			}
		//cout<<endl;
		}
	
	//cout<<"final ordering of vertices"<<endl;
	
	/*for(int y = 0; y<si; y++)
	{
		cout<<v1.at(y)<<endl;
	}*/
	cout<<"n = 5000"<<endl<<"q = 0.0001"<<endl<<"# F E = "<<f1<<endl<<"# B E = "<<b1<<endl<<"# F E 2 = "<<f2<<endl<<"# B E 2 = "<<b2<<endl;
}
