#pragma once
#include <thread>
#include <mutex>
#include <iostream>
#include <vector>
#include <random>

namespace dz6
{
	class Pcout : public std::ostringstream
	{
	public:
		Pcout() = default;

		~Pcout()
		{
			std::lock_guard<std::mutex> guard(m_);
			std::cout << this->str();
		}

	private:
		static std::mutex m_;;
	};
	std::mutex Pcout::m_{};

	void TestPcout()
	{	
		Pcout{ } << "Test pcout" << std::endl;
		std::thread t1([]()
			{
				Pcout{ } << "Thread: " << std::this_thread::get_id() << std::endl;
			});

		std::thread t2([]()
			{
				Pcout{ } << "Thread: " << std::this_thread::get_id() << std::endl;
			});

		
		t1.join();
		t2.join();
		Pcout{} << "Hello world" << std::endl;

		std::vector<std::thread>pcouts;
		int worker = 0;
		for (int i = 0; i < 5; ++i)
		{
			pcouts.emplace_back([&]()
				{
					Pcout{ } << "\tThis is worker " << ++worker << " in thread "
						<< std::this_thread::get_id() << std::endl;
				});
		}
		for (auto& thread : pcouts)
		{
			thread.join();
		}
		Pcout{ } << "Test pcout is Ok" << std::endl;
	}

	int PrimeNumber(int count)
	{
		int result{};
		int i{ 3 };
		while (true)
		{
			bool check = true;
			for (int j = 3; j < static_cast<int>(sqrt(i) + 1); j += 2)
			{
				if (i % j == 0) {
					check = false;
					break;
				}
			}
			if (check)
			{
				--count;
				result = i;
				if (!(count - 1))
				{
					return result;
				}
			}
			else
			{
				check = true;
			}
			i += 2;
		}
		return {};
	}

	void ThreadPrimeNumber()
	{
		int result{};
		std::mutex m;
		int count{};
		Pcout{ } << "Please enter a number that return prime number: ";
		std::cin >> count;
		Pcout{ } << "Your prime number: ";	
		std::thread t1([&]()
			{
				std::lock_guard<std::mutex>g(m);
				result = PrimeNumber(count);
			});

		std::thread t2([&]()
			{
				std::this_thread::sleep_for(0.5s);
				std::lock_guard<std::mutex>g(m);
				Pcout{ } << result << std::endl;
			});
		t1.join();
		t2.join();
	}

	void TestOwen()
	{
		std::vector<int> owen;
		std::mutex m;
		std::random_device rd;
		std::mt19937 mt(rd());
		for (int i = 0; i < 10; ++i)
		{
			std::thread t1([&]()
				{
					std::this_thread::sleep_for(1s);					
					int number = mt();
					std::lock_guard<std::mutex>g(m);
					owen.push_back(number);
					std::cout << "Before erase number" << std::endl;
					for (const auto& n : owen)
					{
						std::cout << n << " ";
					}
					std::cout << std::endl;
				});

			std::thread t2([&]()
				{
					std::this_thread::sleep_for(0.5s);
					std::lock_guard<std::mutex>g(m);

					auto it = std::max_element(owen.begin(), owen.end());					
					if (it != owen.end())
					{
						std::cout << "Erase number: " << *it << std::endl;
						owen.erase(std::remove(owen.begin(), owen.end(), *it));
					}
										
					
				});
			t1.join();
			t2.join();
		}
		std::cout << "Here is what is left: " << std::endl;
		for (const auto& n : owen)
		{
			std::cout << n << " ";
		}
	}
	void Dz6()
	{
		TestPcout();
		ThreadPrimeNumber();
		TestOwen();
	}
}

