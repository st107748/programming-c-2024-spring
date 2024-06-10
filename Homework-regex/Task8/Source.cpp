#include <iostream>
#include <regex>
#include <vector>
bool ex_match(const std::string& s)
{
	std::regex pattern("[+-]?[1-9][0-9]*|0");
	return regex_match(s, pattern);
}
bool ex_search(const std::string& s)
{
	std::regex pattern("^[+-]?[1-9][0-9]*$");
	return regex_search(s, pattern);
}

int main() {
	std::vector<std::string> test = { "001123", "+0123", "-123", "+ghnc00" };
	for (std::string st : test) {
		std::cout << st << ": " << "ex_match: " << ex_match(st) << std::endl;
		std::cout << st << ": " << "ex_search: " << ex_search(st) << std::endl;
		std::cout << "\n";
	}
	return 0;
}