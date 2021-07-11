#include "ls/OrderedMap.h"
#include "iostream"

using namespace std;

using ls::OrderedMap;

int main()
{
	OrderedMap<string, string> om;
	om.push("b", "2");
	om.push("a", "1");
	om.push("c", "3");
	om.replace("a", "4");

	for(auto &it : om.getData())
		cout << it -> first << " " << it -> second << endl;

	return 0;
}
