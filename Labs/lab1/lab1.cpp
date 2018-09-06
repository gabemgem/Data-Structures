#include <iostream>

using namespace std;

int main()	{
	int length;
	float nums[100];
	cin>>length;
	for(int i=0; i<length; i++)
		cin>>nums[i];
	float avg;
	for(int j=0; j<length; j++)
		avg+=nums[j];
	avg/=length;
	cout<< avg << endl;
	for(int k=0; k<length; k++)	{
		if(nums[k]<avg)
			cout<< nums[k] << endl;
	}
	
	
}