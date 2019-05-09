#include <iostream>
#include "GA.h"

using namespace std;
using std::chrono::duration_cast;
using std::chrono::seconds;
typedef std::chrono::high_resolution_clock m_clock;

//GLOBAL CLASSES
GA m_Genetic;

void Main() {
	Console_ColoredTEXT("Genetic Algorithm\n~Henry Oliver\nOptions:\n1. Normal Mode\n2. Debug Mode\n3. Quit\nPlease Select An Option: ", 15);
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
	bool AFound = true;
	FAMILY winner;
	string tmp1;
	string tmp;

	while (true) {

		Main();

		tmp = ""; //reset for loop
		solutionFound = false;
		AFound = true;
		winner.PA.m_string = "";
		winner.PB.m_string = "";

		while (tmp.length() < 1) {

			tmp1 = "";
			tmp = "";

			Console_ColoredTEXT("Please Input A String: ", 15);

			cin >> tmp1;

			getline(cin, tmp);

			tmp = tmp1 + tmp;

		}

		m_Genetic.Target = tmp;

		auto start = m_clock::now();
		m_Genetic.Init(m_Genetic);

		while (!solutionFound) {
			m_Genetic.CalcFitness(m_Genetic);
			winner = m_Genetic.Tournament(m_Genetic);
			if (winner.PA.m_string == m_Genetic.Target || winner.PB.m_string == m_Genetic.Target) {
				if (winner.PB.m_string == m_Genetic.Target) {
					AFound = false;
				}
				solutionFound = true;
				break;
			}
			m_Genetic.Reproduce(m_Genetic, winner);
		}
		auto end = m_clock::now();
		string m_win;
		if (AFound) {
			m_win = "\nFound Solution: " + winner.PA.m_string + "\nTime Taken: " + std::to_string(duration_cast<seconds>(end - start).count()) + " Seconds\n";
		}
		else {
			m_win = "\nFound Solution: " + winner.PB.m_string + "\nTime Taken: " + std::to_string(duration_cast<seconds>(end - start).count()) + " Seconds\n";
		}
		Console_ColoredTEXT(m_win, 10);
		Console_ColoredTEXT("\nDone\n", 10);
		cout <<
		system("pause");
		system("cls");
	}

	return 0;
}