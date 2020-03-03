#include<iostream>
#include<vector>
using namespace std;
int n=3;
vector<vector<int> > no(3);  

void display(int m1, int m2)
{
    m1--;
    m2--;
    int val=no[m1][no[m1].size()-1];
    no[m1].pop_back();
    no[m2].push_back(val);
    for(int k=0; k<3; k++)
    {
        cout<<"--";
        for(int i=0; i<no[k].size(); i++) cout<<no[k][i]<<" ";
        cout<<endl;
    }
}
int moves=0;
void toh(int n, int a, int b, int c)
{
    if(n<=0) return;
    toh(n-1, a, c, b);
    cout<<"-------------"<<endl;
    cout<<"Move from "<<a<<" "<<c<<endl;
    display(a, c);
    moves++;
    toh(n-1, b, a, c);
}
int main()
{
    for(int i=0; i<n; i++) no[0].push_back(i);
    toh(n,1, 2, 3);
    cout<<"No of moves: "<<moves<<endl;
    return 0;
}
