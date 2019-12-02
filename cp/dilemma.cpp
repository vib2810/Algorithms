#include<stdio.h> 
#include<bits/stdc++.h>
using namespace std; 

int main() 
{ 
   int t;
   cin>>t;
   for(int q=0; q<t; q++)
   {
      string n;
      cin>>n;
      bool val=false;
      for(int i=0;i<n.length();i++)
      {
         int temp;
         temp=n[i]-'0';
         if(temp==1) val=!val;
      }
      if(val==true) cout << "WIN" << endl;
      else cout << "LOSE" << endl;
   }
}
