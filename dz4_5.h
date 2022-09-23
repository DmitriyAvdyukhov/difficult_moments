#pragma once
#include <vector>
#include <string>
#include <deque>
#include <list>
#include <algorithm>
#include <random>
#include <functional>
#include <cmath>
#include <numeric>
#include <iostream>
#include <cassert>

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

	void TestInsertSorted()
	{
		std::cout << "Test insert sorted" << std::endl;
		std::vector<int>v{ 1,2,3,4,5,7,8,9 };
		InsertSorted(v, 6);
		std::vector<int>v1{ 1,2,3,4,5,6,7,8,9 };
		assert(v1 == v);

		std::deque<int> dec{ 1,2,3,5,6 };
		InsertSorted(dec, 4);
		std::deque<int> dec1{ 1,2,3,4,5,6 };
		assert(dec == dec1);

		std::list<double>lis{ 1.2, 2.5, 3.4, 6.8 };
		InsertSorted(lis, 4.6);
		std::list<double>lis1{ 1.2, 2.5, 3.4, 4.6, 6.8 };
		assert(lis == lis1);
		std::cout << "Test insert sorted is Ok" << std::endl;
	}

	template<typename T>
	void PrintVector(const std::vector<T>& v)
	{
		std::copy(v.begin(), v.end(), std::ostream_iterator<T>(std::cout, " "));
		std::cout << std::endl;
	}

	

	void TestVectors()
	{
		std::cout << "Test Inaccuracy" << std::endl;
		std::random_device rd;
		std::mt19937 mt(rd());
		std::vector<double>v1(100);		
		std::generate(v1.begin(), v1.end(), std::bind(std::uniform_real_distribution<>(0, 100), std::ref(mt)));
		std::vector<int>v2{ v1.begin(), v1.end() };
		PrintVector(v1);
		PrintVector(v2);
		double result = 0.;
		auto Inaccuracy = [](double x, int y)
		{
			return pow((x - y), 2);
		};
		auto res = std::inner_product(v1.begin(), v1.end(), v2.begin(), 0., std::plus<double>(), Inaccuracy);
		std::cout << "Inaccuracy = " << res << std::endl;

		std::cout << "Test Inaccuracy is Ok" << std::endl;
	}

	void Dz4()
	{
		TestInsertSorted();
		TestVectors();
	}


	void Dz5()
	{

	}
}