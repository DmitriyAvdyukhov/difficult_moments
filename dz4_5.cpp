#include "dz4_5.h"

using namespace std::literals;

namespace dz4_5
{
	void TestInsertSorted()
	{
		std::cout << "Test insert sorted"s << std::endl;
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
		std::cout << "Test insert sorted is Ok"s << std::endl;
	}

	void TestVectors()
	{
		std::cout << "Test Inaccuracy"s << std::endl;
		std::random_device rd;
		std::mt19937 mt(rd());
		std::vector<double>v1(100);
		std::generate(v1.begin(), v1.end(), std::bind(std::uniform_real_distribution<>(0, 100), std::ref(mt)));
		std::vector<int>v2{ v1.begin(), v1.end() };
		PrintVector(v1);
		PrintVector(v2);
		auto Inaccuracy = [](double x, int y)
		{
			return pow((x - y), 2);
		};
		auto res = std::inner_product(v1.begin(), v1.end(), v2.begin(), 0., std::plus<double>(), Inaccuracy);
		std::cout << "Inaccuracy = "s << res << std::endl;

		std::cout << "Test Inaccuracy is Ok"s << std::endl;
	}

	void Dz4()
	{
		TestInsertSorted();
		TestVectors();
	}


	void PrintWords(const std::set<std::string>& words, std::ostream& out)
	{
		std::copy(words.begin(), words.end(), std::ostream_iterator<std::string>(out, ", "));
		out << std::endl;
	}

	void TestUniqueWords()
	{
		std::vector<std::string>vec_words{ "qwe"s, "asd"s, "zxc"s, "asd"s, "wer"s, "sdf"s, "xcv"s, "cvb"s };
		std::stringstream str;
		UniqueWords(vec_words.begin(), std::next(vec_words.begin(), 7), str);
		assert("asd, qwe, sdf, wer, xcv, zxc, \n"s == str.str());

		std::list<std::string> list_words{ "qwe"s, "asd"s, "zxc"s, "asd"s, "wer"s, "sdf"s, "xcv"s, "cvb"s };
		std::stringstream str1;
		UniqueWords(list_words.begin(), std::next(list_words.begin(), 7), str1);
		assert("asd, qwe, sdf, wer, xcv, zxc, \n"s == str1.str());
	}


	std::ostream& operator<<(std::ostream& out, const std::multimap<size_t, std::string>& sentences)
	{
		for (const auto& [count, sentence] : sentences)
		{
			out << "Count words in sentens : "s << count << " "s;
			out << sentence << std::endl;
		}
		return out;
	}
	
	size_t CountWordInSentence(const std::string& str)
	{
		std::string_view s = str;
		size_t pos = s.find_first_not_of(' ');
		size_t iter = 0;				
		while (pos + 1)
		{				
			while (s[pos] == ' ' && pos != s.size() - 1)
			{
				++pos;
			}	
			if (pos != s.size() - 1)
			{
				++iter;
			}
			pos = s.find_first_of(' ', pos + 1);
			
			
		}
		return iter;
	}
		
	std::multimap<size_t, std::string> ParseString(const std::string& s)
	{
		std::multimap<size_t, std::string>words;
		std::string_view str = s;
		size_t pos = 0;
		size_t next_pos = 0;
		while (next_pos != std::string::npos)
		{
			next_pos = std::min(str.find('.', pos), std::min(str.find('!', pos), str.find('?', pos)));

			if (next_pos != std::string::npos)
			{
				std::string result = { str.begin() + pos, str.begin() + next_pos + 1};
				auto count = CountWordInSentence(result);

				words.insert({ count, result });
				pos = next_pos + 2;
			}
		}
		return words;
	}

	void TestCountWords()
	{
		std::cout << "Test count words in sentence"s << std::endl;
		auto count = CountWordInSentence("qwe"s);
		assert(1 == count);
		count = CountWordInSentence("qwe  12  df  "s);
		assert(3 == count);
		count = CountWordInSentence("  qwe  12  df  "s);
		assert(3 == count);
		count = CountWordInSentence("  qwe  12  df"s);
		assert(3 == count);
		count = CountWordInSentence("  qwe    df"s);
		assert(2 == count);
		std::cout << "Test count words in sentence is Ok"s << std::endl;
	}

	void TestParserString()
	{
		std::cout << "Test parser string  in sentences"s << std::endl;
		auto words = ParseString("qwe! as zx qw? asd wer    sd xcxc   sd ."s);
		assert(words.find(1)->second == "qwe!"s);
		assert(words.find(3)->second == "as zx qw?"s);
		assert(words.find(5)->second == "asd wer    sd xcxc   sd ."s);
		words = ParseString("qwe. as zx qw! asd xcxc q sd."s);
		assert(words.find(1)->second == "qwe."s);
		assert(words.find(3)->second == "as zx qw!"s);
		assert(words.find(4)->second == "asd xcxc q sd."s);
		std::cout << "Test parser string  in sentences is Ok"s << std::endl;
	}

	void TestMapWords()
	{
		TestCountWords();
		TestParserString();
		std::string str;
		std::getline(std::cin, str);
		auto words = ParseString(str);
		std::cout << words;
	}

	void Dz5()
	{
		TestUniqueWords();
		TestMapWords();
	}
}