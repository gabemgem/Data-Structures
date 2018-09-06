#include <map>
using namespace std;


class ExMap {

	public:
		ExMap();
		ExMap(bool ex);
		ExMap(int v);

		ExMap& operator[](string s);
		bool operator++();
		map<string, ExMap>::iterator find(string s);

		bool isExt();
		int get();

		void ext();


	private:
		map<string, ExMap> data;
		int value;
		bool extend;

};