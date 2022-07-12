#pragma once
#include <string>

class GlobalFunctions
{
public:
	static bool SameText(const std::string a, const std::string b);
	static int Roll(int min, int max);
};
/*bool SameText(const char* a, const char* b)
{
	return _stricmp(a, b) == 0;
}*/

