#include "calcGCD.hpp"

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// ここからコピペ ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

int64_t calcLCM(const int64_t a, const int64_t b)
{
	// if (a * b == 0) return 0;
	return a / calcGCD(a, b) * b;
}