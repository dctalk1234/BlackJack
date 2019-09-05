#pragma once
#include <stdlib.h>
class RandNumGen
{
public:
	RandNumGen();
	RandNumGen(RandNumGen& copy);
	RandNumGen& operator=(RandNumGen& rhs);
	int returnRandNum();
	~RandNumGen();

private:
	int m_randNum;
};

