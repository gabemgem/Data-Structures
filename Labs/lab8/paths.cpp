#include <iostream>

using namespace std;

int recurser(int x, int y) {
	if(x<0 || y<0)
		return 0;
	if(x==0 && y==0)
		return 1;
	return recurser(x-1, y) + recurser(x, y-1);
}

int main() {
	cout<<"x=0, y=0, paths="<<recurser(0,0)<<endl;
	cout<<"x=2, y=1, paths="<<recurser(2,1)<<endl;
	cout<<"x=2, y=2, paths="<<recurser(2,2)<<endl;
	cout<<"x=5, y=5, paths="<<recurser(5,5)<<endl;

	cout<<"\nx=-1, y=0, paths="<<recurser(-1,0)<<endl;
	cout<<"x=-1, y=2, paths="<<recurser(-1,2)<<endl;
	cout<<"x=0, y=-1, paths="<<recurser(0,-1)<<endl;
	cout<<"x=2, y=-1, paths="<<recurser(2,-1)<<endl;
	cout<<"x=-1, y=-1, paths="<<recurser(-1,-1)<<endl;

	return 1;
}