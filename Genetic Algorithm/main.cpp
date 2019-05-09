#include <iostream>
#include "GA.h"

using namespace std;

//GLOBAL CLASSES
GA m_Genetic;

void Main() {
	cout << "Genetic Algorithm\n~Henry Oliver\nOptions:\n1. Normal Mode\n2. Debug Mode\n3. Quit\nPlease Select An Option: ";
	int tmp;
	cin >> tmp;
	if (tmp == 2) {
		m_Genetic.noisy = true;
	}
	else if (tmp == 3) {
		exit(0);
	}
	else {
		m_Genetic.noisy = false;
	}
}


int main() {

	srand(unsigned(time(0)));

	bool solutionFound = false;
	FAMILY winner;
	string tmp1;
	string tmp;

	while (true) {

		Main();

		tmp = ""; //reset for loop
		solutionFound = false;

		while (tmp.length() < 9) {

			tmp1 = "";
			tmp = "";

			cout << "Please Input a string (at least 10 charcters long): ";

			cin >> tmp1;

			getline(cin, tmp);

			tmp = tmp1 + tmp;

		}

		m_Genetic.Target = tmp;

		m_Genetic.Init(m_Genetic);

		while (!solutionFound) {
			m_Genetic.CalcFitness(m_Genetic);
			winner = m_Genetic.Tournament(m_Genetic);
			if (winner.PA.m_string == m_Genetic.Target || winner.PB.m_string == m_Genetic.Target) {
				solutionFound = true;
				break;
			}
			m_Genetic.Reproduce(m_Genetic, winner);
		}

		cout << "\nDone.\n";
		system("pause");
		system("cls");
	}

	return 0;
}