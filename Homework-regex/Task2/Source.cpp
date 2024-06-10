#include <iostream>
#include <regex>

bool ex_match(const std::string& s)
{
	std::regex pattern(".*101.*");
	return regex_match(s, pattern);
}
bool ex_search(const std::string& s)
{
	std::string str = "101";
	return regex_search(s, std::regex(str));
}

int main() {
	std::vector<std::string> test = { "100101", "10111", "-13" };
	for (std::string st : test) {
		std::cout << st << ": " << "ex_match: " << ex_match(st) << std::endl;
		std::cout << st << ": " << "ex_search: " << ex_search(st) << std::endl;
		std::cout << "\n";
	}
	return 0;
}