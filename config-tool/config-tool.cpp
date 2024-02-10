#include "config-tool.h"
#include "input.h"

namespace fs = std::filesystem;

const std::string ConfigParams::conf_file_name = "config.mk";

void ConfigTool::input_params()
{
	params.module_location = input_existing_directory(
		"Enter path to module location: ");
	params.file_name = input_valid_file_name(
		"Enter file to print: ");
	params.print_every_n_sec = input_uint(
		"Enter interval (u_int) in seconds between print: ");
		
	all_set = true;
	written = false;
}

bool ConfigTool::make_config()
{
	if (!all_set)
		return false;
		
	std::ofstream out;
	out.open(params.module_location / params.conf_file_name,
			 std::ios::trunc);
	out << "file_name=" << params.file_name << '\n';
	out << "print_every_n_sec=" << params.print_every_n_sec << '\n';
	out.close();
	
	written = true;
	return true;
}
