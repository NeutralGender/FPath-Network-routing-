#include <iostream>
#include <fstream>
#include <vector>

using std::ofstream;
using std::string;
using std::vector;
using std::pair;
using std::cout;

#pragma once
class Write
{
public:
	Write(string path) : wr(path) {};
	~Write();

	void write_into_file(vector<pair<string, string>>);
	void write_into_file(string,string,string);

private:
	ofstream wr;

protected:


};

