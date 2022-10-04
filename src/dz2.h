#pragma once
#include <cassert>
#include <algorithm>
#include <iterator>
#include <functional>
#include <fstream>
#include <vector>
#include "log_duration.h"

using namespace std::literals;
namespace dz2
{
	template<typename T>
	void Swap(T& lhs, T& rhs)
	{
		T temp(std::move(lhs));
		lhs = std::move(rhs);
		rhs = std::move(temp);
	}

	void RandomFillVector(std::vector<int*>& v, int size)
	{
		std::srand(static_cast<uint16_t>(std::time(0)));
		v.resize(size);
		auto iter = v.begin();
		while (iter != v.end())
		{
			*iter = new int(rand() % 100);
			++iter;
		}
	};

	void DestructVector(std::vector<int*>& vec)
	{
		for (auto ptr : vec)
		{
			delete ptr;
		}
	}

	bool CheckVector(const std::vector<int*>& vec)
	{
		int last = 0;
		for (int* v : vec)
		{
			if (last > *v)
			{
				return false;
			}
			last = *v;
		}
		return true;
	}

	template<typename T>
	void SortPointers(std::vector<T*>& v)
	{
		std::sort(v.begin(), v.end(), [](T* lhs, T* rhs)
			{
				return *lhs < *rhs;
			});
	}

	auto Pred = [](char ch)
	{
		return ch == 'A' || ch == 'a' 
			|| ch == 'E' || ch == 'e' 
			|| ch == 'Y' || ch == 'y' 
			|| ch == 'U' || ch == 'u' 
			|| ch == 'I' || ch == 'i' 
			|| ch == 'O' || ch == 'o';
	};
	
	auto PredFind = [](char ch)
	{
		std::string vowels = "AEIOUYaeiouy";
		return vowels.find(ch) != std::string::npos;
	};

	auto PredFor = [](char ch)
	{
		std::string vowels = "AEIOUYaeiouy";
		for (auto cha : vowels)
		{
			if (ch == cha)
			{
				return true;
			}			
		}
		return false;
	};

	

	template<typename Pred>
	void CountVowels(Pred pred, const std::string& name_function)
	{
		LOG_DURATION_STREAM(name_function, std::cout);
		std::ifstream file{ "./data/War_and_Peace.txt"s };
		if (file)
		{
			auto count = std::count_if(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>(), pred);
			std::cout << "The counts of vowels in War and Peace : " << count << " count" << std::endl;
		}
		else
		{
			std::cout << "File is not correct" << std::endl;
		}		
	}

	auto ForAndFor = [](size_t& count, char ch)
	{
		std::string vowels = "AEIOUYaeiouy";
		for (auto cha : vowels)
		{
			if (ch == cha)
			{
				++count;
			}
		}
	};

	auto ForAndFind = [](size_t& count, char ch)
	{
		std::string vowels = "AEIOUYaeiouy";
		if (vowels.find(ch) != std::string::npos)
		{
			++count;
		}
	};

	void CountVowelsByFor(std::function<void(size_t&, char)> fn, const std::string& name_fuction)
	{
		LOG_DURATION_STREAM(name_fuction, std::cout);
		std::ifstream file{ "./data/War_and_Peace.txt"s };
		if (file)
		{			
			size_t count{};
			for (auto it = std::istreambuf_iterator<char>(file); it != std::istreambuf_iterator<char>(); ++it)
			{
				fn(count, *it);
			}
			std::cout << "The counts of vowels in War and Peace : " << count << " count" << std::endl;
		}
		else
		{
			std::cout << "File is not correct" << std::endl;
		}		
	}


	void TestSwap()
	{
		std::cout << "Test Swap" << std::endl;
		int x1{ 5 };
		int x2{ 6 };
		auto adr_x1 = &x1;
		auto adr_x2 = &x2;
		auto x1_ptr = &x1;
		auto x2_ptr = &x2;
		assert(*x1_ptr == x1);
		assert(*x2_ptr == x2);

		Swap(x1_ptr, x2_ptr);
		assert(*x1_ptr == x2);
		assert(*x2_ptr == x1);
		assert(adr_x1 == &x1);
		assert(adr_x2 == &x2);
		std::cout << "Test Swap is Ok" << std::endl;
	}

	void TestVector()
	{
		std::cout << "\nTest sort vector" << std::endl;
		std::vector<int*> vec;
		RandomFillVector(vec, 1000);
		assert(!CheckVector(vec));
		SortPointers(vec);
		assert(CheckVector(vec));
		DestructVector(vec);
		std::cout << "Test sort vector is Ok" << std::endl;
	}

	void CountVowelsInWarAndPiace()
	{
		std::cout << "\nTest Count Vowels In War And Peace" << std::endl;
		CountVowels(Pred, "Simple predicat");
		CountVowels(PredFind, "Predicat count_if with find");
		CountVowels(PredFor, "Predicat count_if with for");
		CountVowelsByFor(ForAndFind, "For and Find");
		CountVowelsByFor(ForAndFor, "For and For");
		std::cout << "Test Count Vowels In War And Peace is Ok" << std::endl;
	}

	void Dz2()
	{
		TestSwap();
		TestVector();
		CountVowelsInWarAndPiace();		
	}
}