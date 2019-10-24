#include "Read.h"

Read::~Read()
{
	in.close();
}

bool find_str(vector<string>&vect, string str1)
{
	vector<string>::const_iterator p = std::find(vect.cbegin(), vect.cend(), str1);

	if (p != vect.cend())//find
		return 0;
	else
	{
		vect.push_back(str1);
		return 1;
	}
}


void reading_from_file(ifstream &in, vector<string> &unique_addr, vector<pair<string, string>> & addr_link)
{
	string str = "";

	while (!in.eof())
	{
		getline(in, str);
		
		if (!in)
			break;

		//// delimiter position
		size_t pos = str.find(",");

		string str1 = str.substr(0, pos); // from zero to delimiter
		string str2 = str.substr(pos + 1); // from delimiter+1 up to end

		//define unique addr => matr size
		find_str(unique_addr, str1);
		find_str(unique_addr, str2);

		// make addr pair
		addr_link.push_back(std::make_pair(str1, str2));

	}
}

void Read::input(vector<string> &unique_addr,vector<pair<string, string>> &addr_link)
{
	try
	{
		if (!in.is_open())
			throw exception("Open is Failed!");

		reading_from_file(in, unique_addr, addr_link);
	}
	catch (const exception &ex)
	{
		cout << ex.what();
	}
	
}