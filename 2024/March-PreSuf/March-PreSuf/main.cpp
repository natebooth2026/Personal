// Prefixer-Suffixer
// A Nate Booth Production
// March 29th, 2024

//COMMON PREFIXES AND SUFFIXES FROM: https://teacher.scholastic.com/reading/bestpractices/vocabulary/pdf/prefixes_suffixes.pdf

#include <iostream>
#include <string>
#include <vector>

const std::string PRE[23] = { "anti", "de", "dis", "en", "em", "fore", "in", "im", "il", "ir", "inter", "mid", "mis", "non", "over", "pre", "re", "semi", "sub", "super", "trans", "un", "under"};
const std::string POST[29] = { "able", "ible", "al", "ial", "ed", "en", "er", "est", "ful", "ic", "ing", "ion", "tion", "ation", "ition", "ity", "ty", "ive", "ative", "itive", "less", "ly", "ment", "ous", "eous", "ious", "s", "es", "y" };

int main() {
	std::cout << "Prefixer-Suffixer" << std::endl;
	std::cout << "A Nate Booth Production" << std::endl << std::endl;

	bool quit = false;
	while (!quit) {
		std::vector<std::string> words;
		std::string word;

		//collects input
		std::cout << "Enter a non-punctuated line (\"q\" to quit): ";

		while (std::cin.peek() != '\n') {
			std::cin >> word;
			words.push_back(word);
		}
		std::cin.get(); //skips \n

		std::cout << std::endl;

		//checks for quit condition
		if (words[0] == "q" && words.size() == 1) {
			quit = true;
			continue;
		}

		//manipulates words
		srand(time(nullptr));

		int i = 0;
		while (i < words.size()) {
			int chance = rand() % words.size();

			if (chance && words[i].size() >= 4) {
				std::string temp = PRE[rand() % 23];
				temp += words[i];
				words[i] = temp;
				words[i] += POST[rand() % 29];
			}

			++i;
		}

		//prints result
		i = 0;
		while (i < words.size()) {
			std::cout << words[i] << " ";
			++i;
		}
		std::cout << std::endl << std::endl;
	}
}