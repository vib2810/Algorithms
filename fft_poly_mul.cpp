#include<bits/stdc++.h>
#include <complex> 
using namespace std;
class polynomial
{
	int n;
	vector<double> a; //n-1 degree
public:
	void print()
	{
		int zero_count=0;
		for(int i=this->n-1; i>0; i--)
		{
			if(fabs(a[i])<1e-10) zero_count++;
			else break; 
		} 
		this->n=this->n-zero_count;
		for(int i=0; i<zero_count; i++) a.pop_back();
		for(int i=0; i<this->n; i++) 
		{
			cout<<this->a[i];
			if(i!=0) cout<<"*x^"<<i;
			if(i!=this->n-1) cout<<"+";
		}
		cout<<endl;
	}
	vector<complex<double>> fftr(vector<double> a)
	{
		if(a.size()==1)
		{
			vector<complex<double>> ans;
			complex<double> c(a[0],0.0);
			ans.push_back(c);
			return ans;
		}
		vector<double> ae, ao;
		for(int i=0; i<a.size()/2; i++)
		{
			ae.push_back(a[2*i]);
			ao.push_back(a[2*i+1]);
		}
		vector<complex<double>> ye=fftr(ae);
		vector<complex<double>> yo=fftr(ao);
		vector<complex<double>> ans(a.size());
		complex<double> omega=polar(1.0, (2*M_PI)/a.size());
		complex<double> omega_use=polar(1.0, 0.0);
		for(int i=0; i<(a.size()/2); i++)
		{
			ans[i]=ye[i]+omega_use*yo[i];
			ans[i+(a.size()/2)]=ye[i]-omega_use*yo[i];
			omega_use=omega_use*omega;
		}
		return ans;
	}
	vector<complex<double>> ifftr(vector<complex<double>> c)
	{
		if(c.size()==1)
		{
			vector<complex<double>> ans;
			ans.push_back(c[0]);
			return ans;
		}
		vector<complex<double>> ce, co;
		for(int i=0; i<c.size()/2; i++)
		{
			ce.push_back(c[2*i]);
			co.push_back(c[2*i+1]);
		}
		vector<complex<double>> ye=ifftr(ce);
		vector<complex<double>> yo=ifftr(co);
		vector<complex<double>> ans(c.size());
		complex<double> omega=polar(1.0, (2*M_PI)/c.size());
		complex<double> omega_use=polar(1.0, 0.0);
		for(int i=0; i<(c.size()/2); i++)
		{
			ans[i]=(ye[i]+omega_use*yo[i]);
			ans[i+(c.size()/2)]=(ye[i]-omega_use*yo[i]);
			omega_use=omega_use/omega;
		}
		return ans;
	}
	polynomial pad2n(polynomial p, int max2)
	{
		vector<double> as;
		for(int i=0; i<p.n; i++) as.push_back(p.a[i]);
		for(int i=0; i<(2*max2-p.n); i++) as.push_back(0.0);
		polynomial ans(as);
		return as;
	}
	polynomial multiply_poly(polynomial pin)
	{
		//Padding example
		//s1=3, s2=5
		//Total size of the two-> 8*2=16
		int max=(this->n>pin.n)?this->n:pin.n;
		int max2=1;
		while(1)
		{
			if(max2<max) max2=2*max2;
			else break;
		} 
		polynomial p1=pad2n(*this, max2);
		polynomial p2=pad2n(pin, max2);
		
		//FTT results 
		vector<complex<double>> fft1=fftr(p1.a);
		vector<complex<double>> fft2=fftr(p2.a);
		assert(fft1.size()==fft2.size());
		
		//Convolution
		vector<complex<double>> c;
		for(int i=0; i<fft1.size(); i++) c.push_back(fft1[i]*fft2[i]);

		//Inverse FFT
		vector<complex<double>> ca_ans=ifftr(c);
		vector<double> a_ans;
		for(int i=0; i<ca_ans.size(); i++) a_ans.push_back( real(ca_ans[i])/(p1.n) );
		polynomial ans(a_ans);
		return ans;

	}
	polynomial(vector<double> coeffs)
	{
		for(int i=0; i<coeffs.size(); i++) this->a.push_back(coeffs[i]);
		this->n=coeffs.size();
	}
};
int main()
{
	vector<double> a={2.8,3.9,3.3,1.2,3.3};
	vector<double> b={2,3,2,1,1.21,4.23,2,12.543};
	cout<<"The polynomials are: "<<endl;
	polynomial p1(a);
	p1.print();
	polynomial p2(b);
	p2.print();
	cout<<endl;
	cout<<"The answer is: "<<endl;
	polynomial pans=p1.multiply_poly(p2);
	pans.print();
}