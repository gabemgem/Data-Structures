#include "Time.h"
#include <iostream>
#include <cstdlib>
#include <stdint.h>

Time::Time()
{
	hour=0;
	minute=0;
	second=0;
}

Time::Time(uintptr_t h, uintptr_t m, uintptr_t s)
{
	hour=h;
	minute=m;
	second=s;
}

uintptr_t Time::getHour() const
{
	return hour;
}

uintptr_t Time::getMin() const
{
	return minute;
}

uintptr_t Time::getSec() const
{
	return second;
}

void Time::setHour(uintptr_t h)
{
	hour=h;
}

void Time::setMinute(uintptr_t m)
{
	minute=m;
}

void Time::setSecond(uintptr_t s)
{
	second=s;
}

void Time::PrintAmPm()
{
	std::string temp="am";
	if(hour==0)
		std::cout<<"12";
	else if(hour<12)
	{
		std::cout<<hour;
	}
	else if(hour==12)
	{
		std::cout<<hour;
		temp="pm";
	}
	else
	{
		std::cout<<hour-12;
		temp="pm";
	}
	
	if(minute<10)
		std::cout<<":0"<<minute;
	else
		std::cout<<":"<<minute;
	if(second<10)
		std::cout<<":0"<<second;
	else
		std::cout<<":"<<second;
	std::cout<<" "<<temp<<std::endl;
}

bool IsEarlierThan(const Time& t1, const Time& t2)
{
	if(t1.getHour()<t2.getHour())
		return true;
	else if(t2.getHour()<t1.getHour())
		return false;
	else
	{
		if(t1.getMin()<t2.getMin())
			return true;
		else if(t2.getMin()<t1.getMin())
			return false;
		else
		{
			if(t1.getSec()<t2.getSec())
				return true;
			else
				return false;
		}
	}
	
	return false;
}
