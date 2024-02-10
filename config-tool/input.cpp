#include <iostream>
#include <fstream>
#include <filesystem>
#include <limits>
#include <string>

#include <math.h>

unsigned int input_uint(const std::string && prompt)
{
	double value;
	bool correct_input;
	bool valid_uint;
	do {
		std::cout << prompt;
		std::cin >> value;
		correct_input = (std::cin.good() &&
						 std::cin.peek() == '\n' &&
						 std::cin.peek() != EOF &&
						 !std::cin.fail());
		valid_uint = (round(value) == value &&
					  value > 0 &&
					  value <= std::numeric_limits<unsigned int>::max());
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	} while (!(correct_input && valid_uint));
	return value;
}

namespace fs = std::filesystem;

std::string input_existing_directory(const std::string && prompt)
{
	fs::path path;
	do {
		std::cout << prompt;
		std::cin >> path;
	} while (!fs::is_directory(path));
	return fs::canonical(path);
}

std::string input_valid_file_name(const std::string && prompt)
{
	fs::path path;
	fs::path parent;
	fs::path file_name;
	do {
		std::cout << prompt;
		std::cin >> path;
		parent = path.parent_path();
		file_name = path.filename();
	} while (!fs::is_directory(parent) ||
			 fs::is_directory(path)	   ||
			 file_name.empty());
			 
	return fs::canonical(parent) / file_name;
}

