#include "GA.h"
#include <iostream>
void GA::Init(GA& m_GA)
{
	//Create popultation and generate a random string
	m_GA.individuals.resize(pop);
	for (size_t i = 0; i < m_GA.individuals.size(); i++)
	{
		for (size_t j = 0; j < m_GA.Target.length(); j++)
		{
			m_GA.individuals.at(i).m_string += ' ' + rand() % 94;
		}
	}
}

void GA::CalcFitness(GA& m_GA) {
	//Go through population and calcualte each indivuduals score
	for (size_t i = 0; i < m_GA.individuals.size(); i++)
	{
		m_GA.individuals.at(i).m_fitness = 0; //Reset
		for (size_t j = 0; j < m_GA.Target.size(); j++)
		{
			if (m_GA.individuals.at(i).m_string.at(j) == m_GA.Target.at(j)) {
				m_GA.individuals.at(i).m_fitness++;
			}
		}
		//m_GA.individuals.at(i).m_fitness = (m_GA.individuals.at(i).m_fitness/m_GA.Target.size())*100; //give it a score out of 100
	}
}

FAMILY GA::Tournament(GA& m_GA) {
	FAMILY winner;

	INDIVIDUAL won1;
	INDIVIDUAL won2;
	INDIVIDUAL won3;
	INDIVIDUAL won4;

	//25%
	for (size_t i = 0; i < (m_GA.individuals.size() * 0.25); i++)
	{
		if (m_GA.individuals.at(i).m_fitness > won1.m_fitness) {
			if (m_GA.individuals.at(i).m_string != "") {
				won1 = m_GA.individuals.at(i);
			}
		}
	}
	//25%
	for (double i = 0; i < (m_GA.individuals.size() * 0.25); i++)
	{
		if (m_GA.individuals.at(static_cast<int>(i + (static_cast<double>(m_GA.individuals.size()) * 0.25))).m_fitness > won2.m_fitness) {
			if (m_GA.individuals.at((static_cast<int>(i))).m_string != "") {
				won2 = m_GA.individuals.at((static_cast<int>(i)));
			}
		}
	}
	//25%
	for (double i = 0; i < (m_GA.individuals.size() * 0.25); i++)
	{
		if (m_GA.individuals.at(static_cast<int>(i + (static_cast<double>(m_GA.individuals.size()) * 0.5))).m_fitness > won3.m_fitness) {
			if (m_GA.individuals.at((static_cast<int>(i))).m_string != "") {
				won3 = m_GA.individuals.at((static_cast<int>(i)));
			}
		}
	}
	//25%
	for (double i = 0; i < (m_GA.individuals.size() * 0.25); i++)
	{
		if (m_GA.individuals.at(static_cast<int>(i + (static_cast<double>(m_GA.individuals.size()) * 0.75))).m_fitness > won4.m_fitness) {
			if (m_GA.individuals.at((static_cast<int>(i))).m_string != "") {
				won4 = m_GA.individuals.at((static_cast<int>(i)));
			}
		}
	}
	// Finals

	if (won1.m_fitness > won2.m_fitness) {
		winner.PA = won1;
	}
	else {
		winner.PA = won2;
	}
	if (won3.m_fitness > won4.m_fitness) {
		winner.PB = won3;
		if (winner.PA.m_string == winner.PB.m_string) {
			winner.PB = won4;
		}
	}
	else {
		winner.PB = won4;
		if (winner.PA.m_string == winner.PB.m_string) {
			winner.PB = won3;
		}
	}
	

	//Find percentages

	winner.PA.m_fitness = 0;
	winner.PB.m_fitness = 0;

	for (size_t i = 0; i < m_GA.Target.size(); i++)
	{
		if (winner.PA.m_string.at(i) == m_GA.Target.at(i)) {
			winner.PA.m_fitness++;
		}
		if (winner.PB.m_string.at(i) == m_GA.Target.at(i)) {
			winner.PB.m_fitness++;
		}
	}

	std::cout << "\nBest Parents Found:\n" << winner.PA.m_string << " with " << roundf(winner.PA.m_fitness / m_GA.Target.size() * 100) << "% match " << "and " << winner.PB.m_string << " with " << roundf(winner.PB.m_fitness / m_GA.Target.size() * 100) << "% match";
	
	return winner;
}

void GA::Reproduce(GA & m_GA, FAMILY winner)
{
	for (size_t i = 0; i < m_GA.individuals.size(); i++) //for each individual make offspring from parents
	{
		int cut = 1 + rand() % m_GA.Target.size() - 1;
		bool aFirst = rand() % 1;
		if (aFirst) {
			m_GA.individuals.at(i).m_string = winner.PA.m_string.substr(0, cut) + winner.PB.m_string.substr(cut, m_GA.Target.size());
		}
		else {
			m_GA.individuals.at(i).m_string = winner.PB.m_string.substr(0, cut) + winner.PA.m_string.substr(cut, m_GA.Target.size());
		}
	}

	//LOOK A BLAST OF RADIATION NOW SOME OF THE CHILDERN ARE MUTATED

	for (size_t i = 0; i < m_GA.individuals.size(); i++) //for each individual make offspring from parents
	{
		bool Mutated = rand() % 2;
		bool SuperMutated = rand() % 2;
		if (Mutated) {
			m_GA.individuals.at(i).m_string.at(rand() % m_GA.Target.size()) = ' ' + rand() % 94;;
			if (SuperMutated) {
				m_GA.individuals.at(i).m_string = "";
				for (size_t j = 0; j < m_GA.Target.size(); j++)
				{
					m_GA.individuals.at(i).m_string += ' ' + rand() % 94;
				}
			}
		}
	}
}

