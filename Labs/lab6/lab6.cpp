#include <vector>
#include <list>
#include <iostream>

using namespace std;


void reverse_vector(vector<int>& v)
{
	unsigned int i=0;
	int temp = 0;
	if(v.size()>0) {
		while(i!=v.size()-1-i && i<v.size()-1-i)
		{
			temp = v[i];
			v[i]=v[v.size()-1-i];
			v[v.size()-1-i]=temp;
			i++;
		}
	}
}

void reverse_list(list<int>& l)
{
	int temp=0; 
	list<int>::iterator i=l.begin();
	list<int>::reverse_iterator ri=l.rbegin();
	for(unsigned int j=0; j<l.size()/2; j++)
	{
		temp=*i;
		*i=*ri;
		*ri=temp;
		i++;
		ri++;
	}
	
}

void print(const vector<int>& v)
{
	cout<<"Vector of size: "<<v.size()<<endl;
	cout<<"Contents:\n";
	for(unsigned int i=0; i<v.size(); i++)
		cout<<v[i]<<" ";
	cout<<endl<<endl;
}

void print(const list<int>& l)
{
	cout<<"List of size: "<<l.size()<<endl;
	cout<<"Contents:\n";
	list<int>::const_iterator i;
	for(i=l.begin(); i!=l.end(); i++)
		cout<<*i<<" ";
	cout<<endl<<endl;
}


int main(int argc, char** argv)
{
	vector<int> v1, v2, v3, v4;
	
	v2.push_back(10);
	
	for(int i=1; i<10; i++) {
		v3.push_back(i);
		v4.push_back(i);
	}
	
	v4.push_back(10);
	
	
	cout<<"v1:\n";
	print(v1);
	reverse_vector(v1);
	cout<<"reversed:\n";
	print(v1);
	
	cout<<"\nv2:\n";
	print(v2);
	reverse_vector(v2);
	cout<<"reversed:\n";
	print(v2);
	
	cout<<"\nv3:\n";
	print(v3);
	reverse_vector(v3);
	cout<<"reversed:\n";
	print(v3);
	
	cout<<"\nv4:\n";
	print(v4);
	reverse_vector(v4);
	cout<<"reversed:\n";
	print(v4);
	
	cout<<"---------------------------\n\n";
	
	
	list<int> l1, l2, l3, l4;
	
	l2.push_back(10);
	
	for(int i=1; i<10; i++) {
		l3.push_back(i);
		l4.push_back(i);
	}
	
	l4.push_back(10);
	
	
	cout<<"l1:\n";
	print(l1);
	reverse_list(l1);
	cout<<"reversed:\n";
	print(l1);
	
	cout<<"\nl2:\n";
	print(l2);
	reverse_list(l2);
	cout<<"reversed:\n";
	print(l2);
	
	cout<<"\nl3:\n";
	print(l3);
	reverse_list(l3);
	cout<<"reversed:\n";
	print(l3);
	
	cout<<"\nl4:\n";
	print(l4);
	reverse_list(l4);
	cout<<"reversed:\n";
	print(l4);
	
	
	return 1;
}