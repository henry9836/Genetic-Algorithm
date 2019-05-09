#pragma once
#include <string>
#include <vector>
#include <ctime>
#include <math.h>
#include "ConsoleController.h"

using namespace std;

class INDIVIDUAL {
public:
	float m_fitness = 0;
	string m_string = "";
};

class FAMILY {
public:
	INDIVIDUAL PA;
	INDIVIDUAL PB;
};

class GA {
public:
	void Init(GA& m_GA);
	void CalcFitness(GA& m_GA);
	FAMILY Tournament(GA& m_GA);
	void Reproduce(GA& m_GA, FAMILY winner);

	int pop = 3000;
	vector<INDIVIDUAL> individuals;
	string Target;
	bool noisy = false;
};