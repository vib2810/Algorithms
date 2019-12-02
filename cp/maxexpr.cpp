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
      double k[n], c[n], x[n];
      for(int j=0; j<n; j++)
      { 
         cin>>k[j];
      }
      for(int j=0; j<n; j++)
      { 
         cin>>c[j];
      }
      double kici=0, kii=0, lambda=0;
      for(int p=0; p<n;p++)
      {
         kici+= k[p]*c[p];
         kii+= (1/k[p]);
      }
      double l2= (kii/(4.0*kici));
      if(l2<0) 
      {
         cout<<"-1"<<endl;
         continue;
      }
      else
      {
         lambda=sqrt(l2);
      }
      double F=0;
      for(int i=0; i<n;i++)
      {
         x[i]= ( 1/ (4*pow(lambda,2)*pow(k[i],2)) ) - c[i] ;
         F+= sqrt(c[i]+x[i]);
      }
      cout<<F;
      for(int i=0; i<n;i++)
      {
         cout<<" "<<x[i]; 
      }
      cout <<endl;
   }
}
