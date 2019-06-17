// KRsolution.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <map>

using namespace std;
inline bool space(char c) {
	return c == ' ';
}

inline bool notspace(char c) {
	return c != ' ';
}

vector<string> split(const string& s) {
	using iter = string::const_iterator;
	vector<string> ret;
	iter i = s.cbegin();
	while (i != s.cend()) {
		i = find_if(i, s.end(), notspace);
		iter j = find_if(i, s.end(), space);
		if (i != s.end()) {
			ret.push_back(string(i, j));
			i = j;
		}
	}
	return ret;
}

using str_pair = pair<string, string>;

vector<str_pair> read_from_file(string&& file_name)
{
	string line;
	vector<str_pair> res;
	ifstream in{ file_name };
	if (in.is_open())
	{
		while (getline(in, line))
		{
			auto split_line = split(line);
			if (split_line.size() == 2)
			{
				res.push_back(move(str_pair(split_line[0], split_line[1])));
			}
		}
	}
	else
	{
		throw exception("Error");
	}
	return res;
}

bool cmp(const pair<string, int>& left,const pair<string, int>& right)
{
	return left.second > right.second;
}

void write_result_to_file(vector<pair<string, int>>& vec)
{
	ofstream out;
	out.open("./result.txt");
	if (out.is_open())
	{
		for (auto it = vec.cbegin(); it < vec.end(); it++)
		{
			out << (*it).first << " " << (*it).second << endl;
		}
	}
}

int main()
{
	setlocale(LC_ALL, "RUSSIAN");
	auto res = read_from_file("listStudent.txt");
	map<string,int> rang_lang;
	for (auto it = res.cbegin(); it != res.end(); it++)
	{
		auto& lang = (*it).second;
		auto key_iterator = rang_lang.find(lang);
		if (key_iterator == rang_lang.end())
		{
			rang_lang[lang] = 0;
		}
		rang_lang[lang]++;
	}
	vector< pair<string, int> > vec_lang{ rang_lang.begin(),rang_lang.end() };
	sort(vec_lang.begin(), vec_lang.end(), cmp);
	write_result_to_file(vec_lang);
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
