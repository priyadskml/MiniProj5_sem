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



//int n = 8;
//int G[8][8]={0};
//double q = 0.5;
/*typedef list< int >  list_int;
int main()
{
int visited[8] = {0};
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

        cout<<"underflow\n";

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

            cout<<"error\n";

        }

    }

}            

void topo(int *v, int am[][8], int i)

{

    q = new node_info;

    q->no = i;

    q->st_time = c;

     push(q);

    v[i] = 1;

    for (int j = 0; j < 8; j++)

    {

        if (am[i][j] == 0  || (am[i][j] == 1 && v[j] == 1))

            continue;

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

void topo1(int *v, int am[][8], int i)

{

    v[i] = 1;

    remove(i);

    cout<<i;

    for (int j = 0; j < 8; j++)

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

    
    int v[8], am[8][8], amt[8][8];

    for (int i = 0; i < 8; i++){
		v[i] = 0;}
		    for (int i = 0; i < 8; i++)

    {

        cout<<"enter the values for adjacency matrix row:"<<i + 1<<endl;

        for (int j = 0; j < 8; j++)

        {

            cin>>am[i][j];

        }

    }/*
srand (unsigned ( time(0) ) );
for(int x = 0; x < 8; x++)
{
	for(int y = x; y < 8; y++)
	{
		if(x==y)
		{
			am[x][y] = 0;
		}
		else
		{
			double p_ = ((double) rand()/RAND_MAX);
			//cout<<p<<endl;
			if(p_ < 0.5)
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
*/
    topo(v, am, 0);

    for (int i = 0; i < 8; i++)

    {

        v[i] = 0;

        for (int j = 0; j < 8; j++)

            amt[j][i] = am[i][j];

    }

    while (head != NULL)

    {

        cout<<"Strongly Connected Components:\n";                 

            topo1(v, amt, (head->pt1)->no);

    }
}
//list_int topological_sort()
