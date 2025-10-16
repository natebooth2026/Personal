// Threading
// A Nate Booth Production
// July 31st, 2024

#include <iostream>
#include <thread>

bool wait(int = 0);

int main() {
	std::cout << "Threading\n" << "A Nate Booth Production\n\n";

	std::thread t1(wait, 20);

	std::cout << "You must wait for something to happen...\n";
	wait(3);
	std::cout << "Are you patient enough?\n\n";
	wait(3);
	std::cout << "No?\n";
	wait(3);
	std::cout << "Too bad.\n\n";
	wait(1);
	std::cout << "Loading...\n";
	t1.join();

	std::cout << "You waited for nothing. Good bye.\n\n";
	
	std::thread t2(wait, 20);
	int secondsLeft = 20;
	std::cout << "The program closes in " << secondsLeft << " seconds.\r";

	while (wait(1)) {
		if (secondsLeft - 1 != 1) std::cout << "The program closes in " << --secondsLeft << " seconds. \r" << std::flush;
		else { std::cout << "The program closes in " << --secondsLeft << " second. \r" << std::endl; break; }
	}

	t2.join();
}

bool wait(int s) {
	time_t currentTime = time(nullptr);
	while (time(nullptr) != currentTime + s) {}
	return true;
}