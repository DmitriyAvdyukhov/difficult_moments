#pragma once
#include <vector>
#include <string>
#include <deque>
#include <list>
#include <algorithm>
#include <random>
#include <functional>
#include <cmath>
#include <set>
#include <map>
#include <numeric>
#include <iostream>
#include <cassert>
#include <sstream>

namespace dz4_5
{
	template<typename Conteiner, typename T>
	void InsertSorted(Conteiner& con, T value)
	{
		auto it = std::lower_bound(con.begin(), con.end(), value);
		size_t dis = std::distance(con.begin(), it);
		Conteiner new_con;
		std::copy(con.begin(), std::next(con.begin(), dis), std::back_inserter(new_con));
		new_con.push_back(value);
		std::copy(std::next(con.begin(), dis), con.end(), std::back_inserter(new_con));
		std::swap(con, new_con);
	}

	void TestInsertSorted();

	template<typename T>
	void PrintVector(const std::vector<T>& v)
	{
		std::copy(v.begin(), v.end(), std::ostream_iterator<T>(std::cout, " "));
		std::cout << std::endl;
	}

	void TestVectors();

	void Dz4();

	void PrintWords(const std::set<std::string>& words, std::ostream& out = std::cout);

	template<typename Iterator>
	void UniqueWords(Iterator begin, Iterator last, std::ostream& out = std::cout)
	{
		std::set<std::string>words{ begin, last };
		PrintWords(words, out);
	}

	void TestUniqueWords();

	std::ostream& operator<<(std::ostream& out, const std::multimap<size_t, std::string>& sentences);

	size_t CountWordInSentence(const std::string& str);

	std::multimap<size_t, std::string> ParseString(const std::string& s);

	void TestCountWords();

	void TestParserString();

	void TestMapWords();

	void Dz5();
}