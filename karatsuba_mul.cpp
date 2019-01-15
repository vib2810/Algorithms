#include <bits/stdc++.h>
using namespace std;

//A data structure to store an integer as a string with sign
typedef struct node
{
	string str;
	int sign=1; //1 +ve ,-1 -ve
}string_num;

//A function to find larger of 2 strings of SAME size
int find_larger(string x, string y)
{
    for(int i=0;i<x.size();i++)
    {
        int u=(int)x[i]-48, d=(int)y[i]-48;
        if(u>d) return 1;
        if(u<d) return -1;
        if(u=d) continue;
    }
    return 0;
}

//Removes all the extra zeros that are added in front of a number. Very Important as we calculate m from string length
void remove_zeros(string &x)
{
    if(x.size()==1) return;
    int zeros=0;
    for(int i=0;i<x.size();i++)
    {
        if(x[i]=='0') zeros++;
        else break;
    }
    string x_new(x.size()-zeros,'0');
    for(int i=0;i<x_new.size();i++)
    {
        x_new[i]=x[i+zeros];
    }
    x=x_new; 
}

//makes 2 strings of the same size with 0 padding
void make_same_size(string_num &x, string_num &y)
{
    //remove extra zeros
    remove_zeros(x.str);
    remove_zeros(y.str);
	
    int l1=x.str.size(), l2= y.str.size();
	if(l1>l2); 
	{
		for(int i=0; i<l1-l2; i++)
		{
			y.str='0'+y.str;
		}
	}
	if(l1<l2); 
	{
		for(int i=0; i<l2-l1; i++)
		{
			x.str='0'+x.str;
		}
	}
}
// add/subtract 2 numbers. returns with proper sign bit
string_num add(string_num x, string_num y)
{
	make_same_size(x,y);
	string ans(x.str.size(),'0');
	int carry =0;
	if((x.sign>0 && y.sign>0)||(x.sign<0 && y.sign<0)) //both +ve or negative numbers
    { 
        for(int i=x.str.size()-1;i>=0;i--)
       {
           int u=(int)x.str[i]-48, d=(int)y.str[i]-48;
           int a=u+d+carry;
           ans[i]=a%10+48;
           carry = a/10;
       }
       if(carry!=0) ans=(char)(carry+48)+ans;
       string_num ret;
       ret.str=ans;
       ret.sign=x.sign;
       return ret;
    }
    else
    {
        int a=find_larger(x.str,y.str);
        if(a>0)
        {
            for(int i=x.str.size()-1;i>=0;i--)
            {
                int u=(int)x.str[i]-48, d=(int)y.str[i]-48;
                int var=u-d-carry;
                if(var>=0)
                {
                    ans[i]=var%10+48;
                    carry = 0;  
                }
                if(var<0)
                {
                    int c=0;
                    while((var)<0)
                    {
                        var=var+10;
                        c++;
                    }
                    ans[i]=var+48;
                    carry=c;
                }
            }
        }
        if(a<0)
        {
            for(int i=x.str.size()-1;i>=0;i--)
            {
                int u=(int)y.str[i]-48, d=(int)x.str[i]-48;
                int var=u-d-carry;
                if(var>=0)
                {
                    ans[i]=var%10+48;
                    carry = 0;  
                }
                if(var<0)
                {
                    int c=0;
                    while((var)<0)
                    {
                        var=var+10;
                        c++;
                    }
                    ans[i]=var+48;
                    carry=c;
                }
            }
        }
        if(a==0) ans="0";
        remove_zeros(ans);
        string_num ret;
        if(a>0)ret.sign=1;
        else ret.sign=-1;
        ret.sign*=x.sign;//if -55+100 is passed it will compute 100-55. hence we correct this error
        ret.str=ans;
        return ret;
    }
}

string_num karat(string_num x, string_num y)
{
	make_same_size(x,y); //make x and y of the same size
	if(x.str.size()==1) //base case
	{
		int res= stoi(x.str)* stoi(y.str);
		string_num ans;
        stringstream ss;
        ss << res;
        ans.str = ss.str();
        ans.sign=x.sign*y.sign;
		return ans;
	}

	string_num xl, xr, yl, yr;
	int m=(int)x.str.size()/2;
    //compute xl and yl with the given m
	for(int i=0; i<x.str.size()-m;i++)
	{
		xl.str=xl.str+x.str[i];
		yl.str=yl.str+y.str[i];
	}
    //compute xr and yr with the given m
	for(int i=x.str.size()-1; i>=x.str.size()-m;i--)
	{
		xr.str=x.str[i]+xr.str;
		yr.str=y.str[i]+yr.str;
	}
	string_num ans, xlyl, p2, xryr, nxlyl, nxryr;
	
    //The algo implementation with B=10
    xlyl=karat(xl,yl);
	xryr=karat(xr,yr);

    //compute negative xlyl and xryr to add to p2
    nxlyl.str=xlyl.str;
    nxlyl.sign=-1*xlyl.sign;
    nxryr.str=xryr.str;
    nxryr.sign=-1*xryr.sign;
    
	p2=karat(add(xl,xr),add(yl,yr));//-xlyl-xryr;
    p2=add(p2,nxlyl);
    p2=add(p2,nxryr);

	for(int i=0;i<2*m;i++)//compute xlyl*10^m
	{
		xlyl.str=xlyl.str+'0';
	}
	for(int i=0;i<m;i++)//compute p2*10^m/2
	{
		p2.str=p2.str+'0';
	}
    //final results
	ans=add(xlyl,p2);
	ans=add(ans,xryr);
    ans.sign=x.sign*y.sign;
    //For Debugging
    // cout<< xl.str<< "*"<< "10^"<<m<<"+" << xr.str <<endl << yl.str<< "*" <<"10^"<<m<<"+"<< yr.str<< " m="<< m<<endl;
    // cout<< "addition terms"<< xlyl.str<< "+"<< p2.str<<"+"<< xryr.str<<endl;
	return ans;

}
int main()
{
    string_num a,b;
	a.str="31415926524879777777777722985723957913287590317593485793175329847583275832745";
	b.str="27182818257934758032758374250324759832475342657324785632847563258732450234058";
	string_num ans=karat(a,b);
	cout <<ans.sign<<"*"<<ans.str<< " Ans size:"<< ans.str.size()<<endl;
}

