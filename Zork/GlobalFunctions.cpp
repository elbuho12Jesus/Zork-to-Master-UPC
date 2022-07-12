#include "pch.h"
#include "utility/GlobalFunctions.h"
// compare if two strings are equal
bool GlobalFunctions::SameText(const std::string a, const std::string b)
{
	return _stricmp(a.c_str(), b.c_str()) == 0;
}
// returns the damage that will be received from the two minimum and maximum damage entered
int GlobalFunctions::Roll(int min, int max)
{
	return (max > 0) ? min + (rand() % (max - min)) : 0;
}