#include <iostream>

#include "Read.h"
#include "Write.h"

#include <vector>
#include <string>
#include <algorithm>

using namespace std;


class FPath
{
public:
	FPath() : INF(126'000), path("G1.csv"), 
							path_write_task4("task4.txt"),
							path_write_task2("task2.txt") 
							{};
	~FPath();

	void read_from_file();
	void make_matrix();
	void matrix_init();
	void floyd_algo();
	void find(string, string);
	void task2();
	void task3();
	void task4();

private:
	const int INF;
	const string path;// = "D:\\Telegram Downloads\\fpath\\G1.csv";
	const string path_write_task4;
	const string path_write_task2;
	vector<pair<string, string>> link_addr; //vector for pair<address,address>
	vector<string> unique_addr; // vector for unique address in raw data, needs for matrix
	vector<vector<int>>a; // weight matrix
	vector<vector<int>>h; // history matrix

protected:

};

FPath::~FPath()
{

}

void FPath::read_from_file()
{
	Read r(path);

	r.input(unique_addr, link_addr);
}

void FPath::matrix_init()
{
	for (size_t i = 0; i < unique_addr.size(); ++i)
	{
		vector<int>temp;
		vector<int>temp_for_history;

		for (size_t j = 0; j < unique_addr.size(); ++j)
		{
			temp.push_back(INF);
			temp_for_history.push_back(0);
		}
		temp[i] = 0;
		a.push_back(temp);
		h.push_back(temp_for_history);
	}
}

void FPath::make_matrix()
{
	vector<string>::const_iterator uit; // const_iterator for unique_addr
	vector<pair<string, string>>::const_iterator lit; // const_iterator for link_addr

	for (uit = unique_addr.cbegin(); uit != unique_addr.cend(); uit++)
	{
		for (lit = link_addr.cbegin(); lit != link_addr.cend(); lit++)
		{
			if (lit->first != lit->second)
			{
				if (*(uit) == lit->first)
				{
					vector<string>::const_iterator p = std::find(unique_addr.cbegin(), unique_addr.cend(), lit->second);

					a[uit - unique_addr.cbegin()][p - unique_addr.cbegin()] = 1;
					a[p - unique_addr.cbegin()][uit - unique_addr.cbegin()] = 1;

					h[uit - unique_addr.cbegin()][p - unique_addr.cbegin()] = p - unique_addr.cbegin();
					h[p - unique_addr.cbegin()][uit - unique_addr.cbegin()] = uit - unique_addr.cbegin();

				}
				if (*(uit) == lit->second)
				{
					vector<string>::const_iterator p = std::find(unique_addr.cbegin(), unique_addr.cend(), lit->first);

					a[uit - unique_addr.cbegin()][p - unique_addr.cbegin()] = 1;
					a[p - unique_addr.cbegin()][uit - unique_addr.cbegin()] = 1;

					h[uit - unique_addr.cbegin()][p - unique_addr.cbegin()] = p - unique_addr.cbegin();
					h[p - unique_addr.cbegin()][uit - unique_addr.cbegin()] = uit - unique_addr.cbegin();

				}
			}
		}
	}

}

void FPath::floyd_algo()
{
	for (size_t k = 0; k < unique_addr.size(); k++) // temp
	{
		for (size_t i = 0; i < unique_addr.size(); i++) // from
		{
			for (size_t j = 0; j < unique_addr.size(); j++) // to
			{
				if (a[i][j] > a[i][k] + a[k][j])
				{
					a[i][j] = a[i][k] + a[k][j];
					h[i][j] = h[i][k];
				}
			}
		}
	}
}

void FPath::find(string from, string to)
{
	cout << "\ntask1:\n";

	vector<string>::const_iterator cit_from = std::find(unique_addr.cbegin(), unique_addr.cend(), from);
	vector<string>::const_iterator cit_to = std::find(unique_addr.cbegin(), unique_addr.cend(), to);

	cout << "From :" << from << " -> " << to << endl;

	cout << "Hops count: " << a[cit_from - unique_addr.cbegin()][cit_to - unique_addr.cbegin()] << endl;

}

void FPath::task3()
{
	cout << "\ntask3:\n";

	int unreachable_count = 0;
	for (size_t i = 0; i < unique_addr.size(); ++i)
	{
		for (size_t j = 0; j < unique_addr.size(); ++j)
		{
			if (a[i][j] != INF)
				continue;
			else if (a[i][j] == INF)
			{
				cout << unique_addr[i] << " - " << unique_addr[j] << endl;
				unreachable_count++;
			}
		}
	}
	if (unreachable_count == 0)
		cout << "No unreachable hosts!\n";
}

void FPath::task2()
{
	cout << "\ntask2:\n";

	Write wr(path_write_task2);

	int max_time = 0;
	vector<pair<string,string>> v_task2;

	for (size_t i = 0; i < unique_addr.size(); ++i)
	{
		for (size_t j = 0; j < unique_addr.size(); ++j)
		{
			if (a[i][j] > max_time)
				max_time = a[i][j];
		}
	}

	cout << "MAX_TIME: " << max_time*2 << " ms" << endl;

	for (size_t i = 0; i < unique_addr.size(); ++i)
	{
		for (size_t j = 0; j < unique_addr.size(); ++j)
		{
			if (a[i][j] == max_time)
				v_task2.push_back(std::make_pair(unique_addr[i], unique_addr[j]));
		}
	}

	wr.write_into_file(v_task2);
}

bool add_if_not_exist(vector<pair<string, string>> v_task4, string stemp, string unique_addr)
{
	for (size_t i = 0; i < v_task4.size(); ++i)
	{
		// path is exist in routing table
		if (v_task4[i] == std::make_pair(stemp, unique_addr) ||
			v_task4[i] == std::make_pair(unique_addr, stemp) ) 
			return 0;
	}
	// path is not exist in table, so we add it to vector for output(task4)
	return true;
}

void add_to_vector(vector<vector<int>>h ,int i, int j ,vector<string>unique_addr, vector<pair<string, string>> &v_task4)
{
	int x = h[i][j];
	string stemp = unique_addr[i];
	
	do
	{
		if (add_if_not_exist(v_task4, stemp, unique_addr[x]))
			v_task4.push_back(std::make_pair(stemp, unique_addr[x]));

		stemp = unique_addr[x];
		int temp = h[x][j];
		x = temp;

	} while (x);
}

void FPath::task4()
{
	cout << "\ntask4: Test\\Test\\task4.txt\n";

	Write wr(path_write_task4);

	vector<pair<string, string>> v_task4;

	for (size_t i = 0; i < unique_addr.size(); ++i)
	{
		for (size_t j = 0; j < unique_addr.size(); ++j)
		{
			if (i != j)
			{
				add_to_vector(h, i, j, unique_addr, v_task4);
			}
		}
	}

	// WRITE INTO FILE: Test\Test\task4.txt
	wr.write_into_file(v_task4);

}

int main()
{
	FPath path;

	path.read_from_file();

	path.matrix_init();
	path.make_matrix();
	path.floyd_algo();

	path.find("192.168.0.5", "192.168.0.1"); // task1
	path.task2();
	path.task3();
	path.task4();

	return 0;
}

