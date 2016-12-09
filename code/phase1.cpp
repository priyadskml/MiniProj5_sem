#include <iostream>     // std::cout
#include <algorithm>    // std::random_shuffle
#include <vector>       // std::vector
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
#include<fstream>

using namespace std;

// random generator function:

int main () {
  srand ( unsigned ( time(0) ) );
  vector<int> myvector;
	ofstream file;
	file.open("graph.txt", fstream::out);
	file<<"c Generating Graph for feedback arc set problem"<<endl;
  // set some values:
  for (int i=0; i<1000; ++i) myvector.push_back(i); // 1 2 3 4 5 6 7 8 9

  // using built-in random generator:
  random_shuffle ( myvector.begin(), myvector.end() );
 int count=0, count2 = 0;
  for (vector<int>::iterator it=myvector.begin(); it!=myvector.end(); ++it)
  	for(vector<int>::iterator it1=it+1; it1!=myvector.end(); ++it1)
	{
		if(((double) rand()/RAND_MAX) < 0.01)
		{
			if(((double) rand()/RAND_MAX) < 0.02)
				{
					file<<"e "<<*it1<<" "<<*it<<endl;
					count++;
				}
			else
				{
					file<<"e "<<*it<<" "<<*it1<<endl;
					count2++;
				}	
	}
	}

//cout << '\n';
file<<"c number of forward edges = "<<count2<<endl;
file<<"c number of backward edges = "<<count<<endl;
file.close();
return 0;
}
