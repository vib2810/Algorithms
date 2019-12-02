#include<stdio.h> 
#include<bits/stdc++.h>
using namespace std; 

int main() 
{ 
   int t;
   cin>>t;
   for(int q=0; q<t; q++)
   {
      long long int n,k;
      cin>>n>>k;
      long long int lambda= (n/k);
      if(lambda%k == 0) cout<< "NO" << endl;
      else cout << "YES" << endl;
   }
}
