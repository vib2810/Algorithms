#include <iostream>
#include <limits.h>
#include<stdio.h>
using namespace std;

int main() 
{
	int t=INT_MAX;
    int i,j,k,n,p=0;

    scanf("%d",&n);

    int arr[2][n+1]; //0 layer rep there or not, 1 rep distance from source

    for(i=0;i<n+1;i++)
    {
        arr[0][i]=0;
        arr[1][i]=INT_MAX;
    }
    arr[0][0]=1; //just include 0th in set so it doesnt come later
    arr[1][1]=0; //Set distance as 0 for the 1st node
    while(p!=n)
    {
    	t=INT_MAX;
        for(i=1;i<n+1;i++)         //get index of smallest path element which is not in the set
		    {
  		  if(arr[0][i]==0) //Element not there in set
 	      {
     		if(t>arr[1][i]) 
			{
				t=arr[1][i];
				j=i;
			}
  		  }
			} 

        arr[0][j]= 1; //include jth in the set

        if(j+1 < n+1)
        {
        	if(arr[0][j+1]==0 && ( arr[1][j+1] > arr[1][j] + 1)) arr[1][j+1] = arr[1][j] + 1; //Update neighbour distances which arent already in the set
        }
        if(3*j < n+1)
        {
        	if(arr[0][j*3]==0 && ( arr[1][j*3] > arr[1][j] + 1)) arr[1][j*3] = arr[1][j] + 1; //Update neighbour distances which arent already in the set
        }
			//printf("j=%d\n",j);
   		//for(k=0;k<n+1;k++) printf("i=%d %d %d\n",k,arr[0][k],arr[1][k]);
			//printf("\n");
        p++;
    }
    printf("%d\n",arr[1][n]);
	return 0;
}