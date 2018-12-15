#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <string>

void file_to_vector(std::string filename, std::vector<char> & filled_vec)
{
	std::ifstream ifs;
	ifs.open(filename, std::ios::in);
	char c;
	while (!ifs.eof())
	{
		ifs.get(c);
		filled_vec.push_back(c);
	}
}

void alpha_occurences(const std::vector<char> & vec, std::vector<std::pair<char, int>> & m_alphabet)
{
	//add alphabet to map
	for (char c = 'a'; c <= 'z'; c++)
	{
		m_alphabet.push_back(std::pair<char, int>(c, 0));
	}

	for (auto it = m_alphabet.begin(); it != m_alphabet.end(); it++)
	{
		int char_count = std::count(vec.begin(), vec.end(), it->first);
		it->second = char_count;
	}
}

void word_occurences(const std::vector<char> & text, std::map<std::string, int> & words)
{
	std::string word = "";
	for (auto & c : text)
	{
		if (isalpha(c))
		{
			word += c;
		} else {
			if (word != "")
			{
				auto it = words.find(word);

				if (it != words.end())
				{
					it->second += 1;
				} else {
					words.insert(std::pair<std::string, int>(word, 1));
				}
				word = "";
			}

		}
	}
}

int main(int argc, char *argv[]) {
	std::cout << "starting.." << std::endl;

	std::vector<char> bible;

	file_to_vector("bible.txt", bible);

	//print character count and number of new lines
	std::cout << "size of bible: " <<  bible.size() << std::endl;
	std::cout << "number of new lines: " << 
		std::count(bible.begin(), bible.end(), '\n') << std::endl;

	//count number of characters
	auto is_char_alpha = [](char & c) { return isupper(c) || islower(c);  };
	int alpha_count = std::count_if(bible.begin(), bible.end(), [&](char c) { return is_char_alpha(c); });
	std::cout << "number of alphabet characters: " << alpha_count << std::endl;

	//make everything lowercase
	auto char_to_lower = [](char & c) { c = tolower(c); };
	std::for_each(bible.begin(), bible.end(), char_to_lower);

	//count occurences of alphabetical characters
	std::vector<std::pair<char, int>> character_count;
	alpha_occurences(bible, character_count);
	auto print_map = [&](std::pair<char, int> p) {std::cout << p.first << " : " << p.second << std::endl; };
	std::for_each(character_count.begin(), character_count.end(), print_map);

	//sort by occurences
	std::sort(character_count.begin(), character_count.end(), [](auto & left, auto & right) {return left.second > right.second;  });
	std::cout << std::endl;
	std::for_each(character_count.begin(), character_count.end(), print_map);

	std::cout << "counting words.." << std::endl;

	//make a map out of every word and how often it occurs
	std::map<std::string, int> word_map;
	word_occurences(bible, word_map);

	//make a new vector of pairs to copy the occurence-maps' content to (in order)
	std::vector<std::pair<std::string, int>> sorted_words(word_map.size());
	std::partial_sort_copy(word_map.begin(), word_map.end(),
		sorted_words.begin(), sorted_words.end(),
		[](const std::pair<std::string, int> & a, const std::pair<std::string, int> & b) {return a.second > b.second; });

	//print top 10
	std::cout << std::endl;
	for (int i = 0; i < 10; i++)
	{
		std::cout << sorted_words[i].first << " : " << sorted_words[i].second << std::endl;
	}

	std::cout << "Press Enter to exit.." << std::endl;
	std::cin.get();
	return 0;
}

