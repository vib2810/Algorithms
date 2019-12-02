#include<stdio.h> 
#include<bits/stdc++.h>
using namespace std; 

int main() 
{ 
   int t;
   cin>>t;
   for(int q=0; q<t; q++)
   {
      int n;
      cin>>n;
      double a[n], b[n];
      double max=-1;
      for(int j=0; j<n; j++)
      { 
         cin>>a[j];
      }
      for(int j=0; j<n; j++)
      { 
         cin>>b[j];
      }
      for(int j=0; j<n; j++)
      { 
         double temp=20*a[j]-10*b[j];
         if(temp<0) temp=0;
         if(temp>max) max=temp;
      }
      cout<<max<<endl;
   }
}
