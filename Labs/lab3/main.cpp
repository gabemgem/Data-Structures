
#include <iostream>

using namespace std;



void compute_squares(unsigned int* a, unsigned int* b, unsigned int n)
{
	
	unsigned int *p;
	unsigned int *g=b;
	for(p=a; p<a+n; p++)
	{
		*g=(*p)*(*p);
		g++;
	}
}

int main()
{
	unsigned int n=5;
	
	unsigned int a[n];
	unsigned int b[n];
	
	for(unsigned int i=0; i<n; i++)
	{
		a[i]=i+1;
		cout<<a[i]<<endl;
	}
	
	cout<<endl;
	
	compute_squares(a, b, n);
	
	for(unsigned int j=0; j<n; j++)
		cout<<b[j]<<endl;
	
	cout<<endl;
	
	a[0]=-1;
	a[1]=6;
	a[2]=0;
	a[3]=10;
	a[4]=1;
	
	for(unsigned int k=0; k<n; k++)
		cout<<a[k]<<endl;
	
	cout<<endl;
	
	compute_squares(a, b, n);
	
	for(unsigned int l=0; l<n; l++)
		cout<<b[l]<<endl;
	
	return 0;
}









