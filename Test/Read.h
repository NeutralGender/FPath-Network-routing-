#include <iostream>
#include <fstream>
#include <exception>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

#pragma once

class Read
{
public:
	Read(string temp) : in(temp) {};
	~Read();
	void input(vector<string>&,vector<pair<string, string>>&);

private:
	ifstream in;
};

