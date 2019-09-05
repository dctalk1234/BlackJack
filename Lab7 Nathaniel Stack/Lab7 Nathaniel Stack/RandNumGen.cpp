#include "RandNumGen.h"



RandNumGen::RandNumGen(): m_randNum((rand() % 52))
{
}

RandNumGen::RandNumGen(RandNumGen & copy)
{
	m_randNum = copy.m_randNum;
}

RandNumGen & RandNumGen::operator=(RandNumGen & rhs)
{
	if (this != &rhs)
	{
		m_randNum = rhs.m_randNum;
	}
	return *this;
}

int RandNumGen::returnRandNum()
{
	return m_randNum;
}


RandNumGen::~RandNumGen()
{
}
