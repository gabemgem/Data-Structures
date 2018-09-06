#include <iostream>
#include <vector>

using namespace std;

int main() {
	vector<char> v1(4, 'a');
	vector<char> v2(4, 'a');
	vector<char> v3(4,'b');
	vector<char> v4(3,'a');

	vector< vector<char> > v5(2, vector<char>(2,'a'));
	vector< vector<char> > v6(2, vector<char>(2,'a'));

	if(v1==v2 && v2!=v3 && v2!=v4)
		cout<<"1d true"<<endl;

	if(v5==v6)
		cout<<"2d true"<<endl;


	return 0;
}