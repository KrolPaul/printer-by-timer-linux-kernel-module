#include "config-tool.h"

int main()
{
	ConfigTool confTool;
	confTool.input_params();
	if (!confTool.make_config())
		return -1;

	return 0;
}
