#include "Point2D.h"
#include "Rectangle.h"
#include <iostream>

using namespace std;

int main()
{
	Rectangle r1 = Rectangle(Point2D(), Point2D(4.0,4.0));
	Rectangle r2 = Rectangle(Point2D(), Point2D(10.0,10.0));
	
	Point2D pt = Point2D();
	
	pt.set(2.0, 2.0);
	pt.set(2.0, 10.0);
	
	print_rectangle(r1);
	cout<<"\n--------------------\n";
	print_rectangle(r2);
	
	cout<<"(1,1)   "<<r1.is_point_within(Point2D(1.0,1.0))
		<<"   "<<r2.is_point_within(Point2D(1.0,1.0))<<endl;;
	cout<<"(5,5)   "<<r1.is_point_within(Point2D(5.0,5.0))
		<<"   "<<r2.is_point_within(Point2D(5.0,5.0))<<endl;
	cout<<"(5,11)   "<<r1.is_point_within(Point2D(5.0,11.0))
		<<"   "<<r2.is_point_within(Point2D(5.0,11.0))<<endl;
	
	cout<<"(11,11)   "<<r1.is_point_within(Point2D(11.0,11.0))
		<<"   "<<r2.is_point_within(Point2D(11.0,11.0))<<endl;
	
	
	cout<<"\n\nAdd point:\n";
	
	cout<<"(1,1)   "<<r1.add_point(Point2D(1.0,1.0))
		<<"   "<<r2.add_point(Point2D(1.0,1.0))<<endl;
	cout<<"(5,5)   "<<r1.add_point(Point2D(5.0,5.0))
		<<"   "<<r2.add_point(Point2D(5.0,5.0))<<endl;
	cout<<"(5,11)   "<<r1.add_point(Point2D(5.0,11.0))
		<<"   "<<r2.add_point(Point2D(5.0,11.0))<<endl;
	cout<<"(11,11)   "<<r1.add_point(Point2D(11.0,11.0))
		<<"   "<<r2.add_point(Point2D(11.0,11.0))<<endl;
	
	
	
	return 0;
}