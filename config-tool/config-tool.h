#pragma once
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

struct ConfigParams{
	static const std::string conf_file_name;
	fs::path module_location;
	fs::path file_name;
	unsigned int print_every_n_sec;
};

class ConfigTool{
public:
	void input_params();
	bool make_config();
	
private:
	bool all_set = false;
	bool written = false;
	
	ConfigParams params;
};	
