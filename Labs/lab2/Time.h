#include <cstdlib>
#include <stdint.h>

class Time	{
	
	private:
		uintptr_t hour;
		uintptr_t minute;
		uintptr_t second;
		
	public:
		Time();
		Time(uintptr_t h, uintptr_t m, uintptr_t s);
		
		//accessors
		uintptr_t getHour() const;
		uintptr_t getMin() const;
		uintptr_t getSec() const;
		
		//modifiers
		void setHour(uintptr_t h);
		void setMinute(uintptr_t m);
		void setSecond(uintptr_t s);
		
		void PrintAmPm();
	
};

bool IsEarlierThan(const Time& t1, const Time& t2);