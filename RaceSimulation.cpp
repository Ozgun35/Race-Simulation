#include <iostream>
#include "time.h"
#include <algorithm>

int runnerNumber;

class Runner {
private:
	int runnerNo;
	float position;
	int rank;
	int tempRank;
	bool isFinished;

public:
	Runner(int newRunnerNo, float newPosition) {
		runnerNo = newRunnerNo;
		position = newPosition;
		rank = 0;
		isFinished = false;
	}

	void run() {
		float speed = rand() % 500 + 100;
		position += speed / 100;
	}

	int getRunnerNo() {
		return runnerNo;
	}

	float getPosition() {
		return position;
	}

	bool getIsFinished() {
		return isFinished;
	}

	int getRank() {
		return rank;
	}

	int getTempRank() {
		return tempRank;
	}

	void setTempRank(int newTempRank) {
		tempRank = newTempRank;
	}

	void setFinished(int newRank) {
		isFinished = true;
		rank = newRank;
	}
};

class Race {
private:
	int numberOfRunners;
	int raceLength;
	Runner *runners[1000];

public:
	Race(int newNumberOfRunners, int newRaceLength) {
		numberOfRunners = newNumberOfRunners;
		for (int i = 0; i < numberOfRunners; i++) {
			runners[i] = new Runner(i + 1, 0);
		}
		raceLength = newRaceLength;
	}

	bool doesRaceContinue() {
		for (int i = 0; i < numberOfRunners; i++) {
			if (runners[i]->getPosition() < raceLength) return true;
		}
		return false;
	}

	void printRankings() {
		for (int i = 0; i < runnerNumber; i++) {
			std::cout << "Runner No: " << runners[i]->getRunnerNo() << "\n";
			std::cout << "Rank: " << runners[i]->getRank() << "\n\n";
		}
	}

	void printTempRankings() {
		float *postionArray{ new float[runnerNumber] {} };
		for (int i = 0; i < runnerNumber; i++) {
			postionArray[i] = runners[i]->getPosition();
		}
		std::sort(postionArray, postionArray + runnerNumber, std::greater<float>());
		for (int i = 0; i < runnerNumber; i++) {
			for (int j = 0; j < runnerNumber; j++) {
				if (postionArray[i] == runners[j]->getPosition()) {
					runners[j]->setTempRank(i + 1);
				}
			}
		}
		for (int i = 0; i < runnerNumber; i++) {
			std::cout << "Runner No: " << runners[i]->getRunnerNo() << "\n";
			std::cout << "Position: " << runners[i]->getPosition() << "\n";
			std::cout << "Temporary Rank: " << runners[i]->getTempRank() << "\n\n";
		}
	}

	void startRace() {
		int rankCounter = 1;
		while (doesRaceContinue()) {
			for (int i = 0; i < numberOfRunners; i++) {
				if (!runners[i]->getIsFinished()) {
					runners[i]->run();
					if (runners[i]->getPosition() >= raceLength) {
						if (rankCounter == 1) {
							printTempRankings();
						}
						runners[i]->setFinished(rankCounter);
						rankCounter++;
					}
				}
			}
		}
		printRankings();
	}

	int getRaceLength() {
		return raceLength;
	}
};

int readInput() {
	bool valid = false;
	do {
		std::cout << "Enter the number of runners(max 1000):";
		std::cin >> runnerNumber;
		if (runnerNumber > 0 && runnerNumber < 1001 && !isdigit(runnerNumber)) valid = true;
		else {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input! ";
		}
	} while (!valid);
	return (runnerNumber);
}

int main() {
	srand(time(NULL));
	Race *race = new Race(readInput(), 100);
	race->startRace();
	return 0;
}
