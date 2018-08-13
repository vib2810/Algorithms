#include <bits/stdc++.h>
#include<unistd.h>
#include <time.h>   
using namespace std;
int n=100;
int rep=100000;
int isvalid(int x,int y)
{
	if(x>=0 && y>=0 && x< n && y< n) return 1;
	return 0;
}
class onion
{
	public:
		int* id;
		int* sz;
		int root(int i)
		{
			while (i != id[i]) 
			{
				id[i]=id[id[i]];
				i = id[i];
			}
			return i;
		}
	public:
		onion(int N) //constructor
		{
			id = new int[N];
			sz = new int[N];
			for (int i = 0; i < N; i++) 
			{
				id[i] = i;
				sz[i] = 1;
			}
			int n=sqrt(N-2);
			//connect virtual nodes
			//Here 0 and n^2+1 nodes are virtual
			for(int i=1;i<n+1;i++)
			{
				this->Union(0,i);
				this->Union(n*n+1,n*n-n+i);
			}
		}
		bool connected(int p, int q)
		{
			return root(p) == root(q);
		}
		void Union(int p, int q)
		{
			int i = root(p);
			int j = root(q);
			if (i == j) return;
			if  (sz[i] < sz[j]) 
			{ 
				id[i] = j; 
				sz[j] += sz[i]; 
			} 
			else   
			{
				id[j] = i; 
				sz[i] += sz[j]; 
			}  
		}
		int per()
		{
			if(this->connected(0,n*n + 1)==1) return 1;
			return 0;
		}
};

int main()
{
	double p_mean=0;
	for(int k=0;k<rep;k++)
	{
		bool grid[n][n];
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			{
				grid[i][j]=0;
			}
		}
		int x,y;
		onion set(n*n + 2);
		float p=0;
		while(set.per()==0)
		{
			srand (time(NULL)+rand());
			x=rand()%n;
			y=rand()%n;
			//If already open skip
			if(grid[x][y]==1) continue;
			else
			{
				p++; // increase the no of open sites
				grid[x][y]=1; //mark site as open in bool array

				//connect each open neighbour with x,y
				if(isvalid(x-1,y))
				{
					if(grid[x-1][y]==1) set.Union( n*(x-1) + y + 1 , n*x + y + 1); // If the neighbour is open then connect the neighbour and x,y
				}

				if(isvalid(x,y-1))
				{
					if(grid[x][y-1]==1) set.Union( n*(x) + (y-1) + 1 , n*x + y + 1);
				}	

				if(isvalid(x+1,y))
				{
					if(grid[x+1][y]==1) set.Union( n*(x+1) + (y) + 1 , n*x + y + 1);
				}	

				if(isvalid(x,y+1))
				{
					if(grid[x][y+1]==1) set.Union( n*(x) + (y+1) + 1 , n*x + y + 1);
				}				
				
			}
		}
		p=p/(n*n);
		cout << k << endl;
		p_mean+=p;
	} 
	p_mean=p_mean/(float)rep;
	cout << "P_Mean" << p_mean << endl;
}