#include "Write.h"

Write::~Write()
{
	wr.close();
}

void Write::write_into_file(vector<pair<string, string>> v_task4)
{
	try
	{
		vector<pair<string, string>>::const_iterator it;
		for (it = v_task4.cbegin(); it != v_task4.cend(); ++it)
			wr << it->first << " -> " << it->second << std::endl;
	}
	catch (...)
	{
		std::cout << "write_into_file error!\n";
	}
}