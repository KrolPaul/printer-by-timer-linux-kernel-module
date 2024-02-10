#pragma once

#include <string>

unsigned int input_uint(const std::string && prompt);

std::string input_existing_directory(const std::string && prompt);
std::string input_valid_file_name(const std::string && prompt);
