#include <bits/stdc++.h>
#include "/home/vib2810/Installations/matplotlib-cpp-master/matplotlibcpp.h"

namespace plt = matplotlibcpp; 
using namespace std;

//compile command :  g++ inversion.cpp -std=c++11 -I/usr/include/python2.7 -lpython2.7 && ./a.out 
double r=6.0;
double degtorad(double theta_deg)
{
	double temp= (theta_deg*3.14159265);
	return temp/(180.0);
}
typedef struct point
{
	double x;
	double y;
	double z;
}Point;

void plotp(Point a, string s)
{
	vector <double> t1;
	t1.push_back(a.x);
	vector <double> t2;
	t2.push_back(a.y);
	plt::plot(t1, t2, "ro");
	plt::annotate(s, a.x, a.y);
	return;
}
void plotl(Point a, Point b)
{
	vector <double> t1;
	t1.push_back(a.x);
	t1.push_back(b.x);
	

	vector <double> t2;
	t2.push_back(a.y);
	t2.push_back(b.y);

	plt::plot(t1, t2);
	return;
}
void plotfill(Point a, Point b, Point c, Point d, Point e, Point f)// Point g, Point h )//, Point i, Point j)
{
	vector <double> t1;
	t1.push_back(a.x);
	t1.push_back(b.x);
	t1.push_back(c.x);
	t1.push_back(d.x);
	t1.push_back(e.x);
	t1.push_back(f.x);
	// t1.push_back(g.x);
	// t1.push_back(h.x);
	// t1.push_back(i.x);
	// t1.push_back(j.x);



	vector <double> t2;
	t2.push_back(a.y);
	t2.push_back(b.y);
	t2.push_back(c.y);
	t2.push_back(d.y);
	t2.push_back(e.y);
	t2.push_back(f.y);
	// t2.push_back(g.y);
	// t2.push_back(h.y);
	// t2.push_back(i.y);
	// t2.push_back(j.y);



	plt::plot(t1, t2);
}
double dist(Point a, Point b)
{
	return sqrt( pow(a.x-b.x, 2) + pow(a.y-b.y, 2) );
}

//Put the new coordinate system at b rotated at theta and give out new coordinates of a
Point shiftcoord(Point a, Point b,double th)
{
	Point ans;
	ans.x = ((a.x-b.x)*cos(degtorad(th)) + (a.y-b.y)*sin(degtorad(th))) ;
	ans.y = ((a.y-b.y)*cos(degtorad(th)) - (a.x-b.x)*sin(degtorad(th))) ;
	cout << dist(ans, b) << endl;
	return ans;
}

//Rotate point a about b by theta(degrees)
Point rotate(Point a, Point b,double th)
{
	Point ans;
	ans.x = ((a.x-b.x)*cos(degtorad(th)) - (a.y-b.y)*sin(degtorad(th))) + b.x;
	ans.y = ((a.y-b.y)*cos(degtorad(th)) + (a.x-b.x)*sin(degtorad(th))) + b.y;
	// cout << dist(ans, b) << endl;
	return ans;
}

Point getline(Point p, double mn, double md)
{
	Point ans;
	if(fabs(md)< 0.000001)
	{
		ans.x= 1;
		ans.y=0;
		ans.z= -p.x;
	}
	else
	{
		ans.x=mn;
		ans.y=-md;
		ans.z=md*p.y-mn*p.x;
	}
	return ans;
}
Point perpen_inter(Point a, Point b, Point c)
{
	Point x1,x2;
	x1.x= (a.x+b.x)/2;
	x1.y= (a.y+b.y)/2;
	x2.x= (b.x+c.x)/2;
	x2.y= (b.y+c.y)/2;
	Point l1=getline(x1, -(b.x-a.x), (b.y-a.y));
	Point l2=getline(x2, -(c.x-b.x), (c.y-b.y));
	Point ans;
	ans.x = (l1.y*l2.z - l2.y*l1.z)/(l1.x*l2.y - l2.x*l1.y);
	ans.y = (l1.z*l2.x - l2.z*l1.x)/(l1.x*l2.y - l2.x*l1.y);
	return ans;

}

int main() 
{ 
	// cout<< "Enter pairwise start point x , y and theta of the line segment "<< endl;
	Point a1, a2, a3, b1, b2, b3;
	double th1, th2 , th3;
	// scanf("%lf %lf %lf", &a1.x, &a1.y,&th1 );
	// cout << "got1" <<endl;
	// scanf("%lf %lf %lf", &a2.x, &a2.y,&th2 );
	// scanf("%lf %lf %lf", &a3.x, &a3.y,&th3 );
	a1.x = 1;
	a1.y=-5;
	a2.x = -0.5;
	a2.y= -0.6;
	a3.x= 0;
	a3.y=0;
	th1= 90;
	th2= 30;
	th3=0;
	int flag;

	if(r*cos(degtorad(th1))>0) flag=1;
	else flag=-1;
	b1.x = a1.x + flag*r*cos(degtorad(th1));
	b1.y= a1.y + flag*r*sin(degtorad(th1));


	if(r*cos(degtorad(th2))>0) flag=1;
	else flag=-1;
	b2.x = a2.x + flag*r*cos(degtorad(th2));
	b2.y= a2.y + flag*r*sin(degtorad(th2));


	if(r*cos(degtorad(th3))>=0) flag=1;
	else flag=-1;
	b3.x = a3.x + flag*r*cos(degtorad(th3));
	b3.y=  a3.y + flag*r*sin(degtorad(th3));

	// plt::xlim(-2, 10);
	// plt::xlim(-2, 10);
	plt::axis("equal");
	plotp(a1, "a1");
	plotp(b1, "b1");
	plotp(a2, "a2");
	plotp(b2, "b2");
	plotp(b3, "b3");
	plotp(a3, "a3");

	// plotl(a1,b1);
	// plotl(a2,b2);
	plotl(a3,b3);

	Point o1, o2;
	o1.x = -1;
	o1.y = -4;
	o2.x= -2;
	o2.y = 5;
	// scanf("%lf %lf", &o1.x , &o1.y);
	// scanf("%lf %lf", &o2.x , &o2.y);
	plotp(o1, "o1");
	plotp(o2, "o2");

	// Point t1 = shiftcoord(b2,a2, 30);
	// plotp(t1, "t1");
	// cout << "t1: "<<t1.x << " " << t1.y << endl;

	//Inverting o1 and o2 at position 3
	Point temp;

	//o1 as seen by 2 on 3
	temp=shiftcoord(o1, a2, th2);
	Point o1_23=shiftcoord(temp, a3, th3);
	plotp(o1_23, "o1_23");

	//o1 as seen by 1 on 3
	temp=shiftcoord(o1, a1, th1);
	Point o1_13=shiftcoord(temp, a3, th3);
	plotp(o1_13, "o1_13");

	//o2 as seen by 2 on 3
	temp=shiftcoord(o2, a2, th2);
	Point o2_23=shiftcoord(temp, a3, th3);
	plotp(o2_23, "o2_23");

	//o2 as seen by 1 on 3
	temp=shiftcoord(o2, a1, th1);
	Point o2_13=shiftcoord(temp, a3, th3);
	plotp(o2_13, "o2_13");

	Point x1= perpen_inter(o1_13, o1_23, o1);
	plotp(x1, "x1");
	Point x2= perpen_inter(o2_13, o2_23, o2);
	plotp(x2, "x2");


	cout << "o1_23: "<<o1_23.x << " " << o1_23.y << endl;
	cout << "o1_13: "<<o1_13.x << " " << o1_13.y << endl;
	cout << "o2_23: "<<o2_23.x << " " << o2_23.y << endl;
	cout << "o2_13: "<<o2_13.x << " " << o2_13.y << endl;
	cout << "x1: "<<x1.x << " " << x1.y << endl;
	cout << "x2: "<<x2.x << " " << x2.y << endl;

	plotfill(a3,x2, x1,x2, x1, b3);
	plotl(o2,x2);
	plotl(o1,x1);


    plt::show();





}

