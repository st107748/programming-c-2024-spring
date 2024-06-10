#include <iostream>
#include <regex>

bool ex_match(const std::string& s)
{
	std::regex pattern("^[0]?[2-9]*$");
	return std::regex_match(s, pattern);
}
bool ex_search(const std::string& s)
{
	std::regex pattern("^[0-9]*$");
	return std::regex_search(s, pattern) && !std::regex_search(s, std::regex("1"));
}

int main() {
	std::vector<std::string> test = { "10123", "acv23", "23777", "Gl33owb" };
	for (std::string st : test) {
		std::cout << st << ": " << "ex_match: " << ex_match(st) << std::endl;
		std::cout << st << ": " << "ex_search: " << ex_search(st) << std::endl;
		std::cout << "\n";
	}
	return 0;
}