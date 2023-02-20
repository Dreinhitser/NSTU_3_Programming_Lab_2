// вариант 9

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>

using namespace std;

typedef vector<string> Strings;

// создание файла со случайными строками
void write_file(string& filename)
{
	ofstream output(filename);

	if (!output.is_open())
	{
		throw runtime_error("Could not open the file");
	}

	const long long strings_count = 54'775;
	const int string_size = 100;

	srand(time(nullptr));

	for (long long i = 0; i < strings_count; i++)
	{
		string s = "";

		for (int j = 0; j < string_size; j++)
		{
			// символы от a до z
			s += rand() % 26 + 97;
		}

		output << s << "\n";
	}

	output.close();
}

map<char, Strings>::iterator find_max_vector(map<char, Strings>& text)
{
	if (text.size() == 0)
	{
		throw  runtime_error("map is empty");
	}

	long max_strings_count = (*text.begin()).second.size();

	map<char, Strings>::iterator iter = text.begin();
	map<char, Strings>::iterator max_iter = iter;

	while (iter != text.end())
	{
		if ((*iter).second.size() > max_strings_count)
		{
			max_strings_count = (*iter).second.size();
			max_iter = iter;
		}
		iter++;
	}

	return max_iter;
}

int main()
{
	map<char, Strings> text;

	string filename = "";
	cout << "Enter filename: ";
	cin >> filename;

	try
	{
		write_file(filename);

		ifstream input(filename);
		if (!input.is_open())
		{
			throw runtime_error("Could not open the file");
		}

		string s = "";
		while (getline(input, s))
		{
			text[s[0]].push_back(s);
		}

		input.close();

		map<char, Strings>::iterator max_iter = find_max_vector(text);

		for (auto& iter : (*max_iter).second)
		{
			cout << iter << "\n";
		}
	}
	catch (runtime_error error)
	{
		cerr << error.what() << "\n";
	}
	catch (exception other_error)
	{
		cerr << other_error.what() << "\n";
	}

	return 0;
}