#include <algorithm>
#include <iomanip>

#include "dz1.h"


namespace dz1
{
	//----------------Person-------------

	Person::Person() = default;

	Person::Person(std::string surna, std::string na, std::optional<std::string> patronym)
		: surname(surna), name(na), patronymic(patronym)
	{}

	std::ostream& operator<<(std::ostream& out, const Person& person)
	{
		out << std::setw(13) << std::right << person.surname << std::setw(10) << std::right << person.name;
		out << std::setw(15) << std::right;
		if (person.patronymic)
		{
			out << *person.patronymic;
		}
		return out;
	}

	bool operator==(const Person& lhs, const Person& rhs)
	{
		return std::tie(lhs.surname, lhs.name, lhs.patronymic) == std::tie(rhs.surname, rhs.name, rhs.patronymic);
	}

	bool operator<(const Person& lhs, const Person& rhs)
	{
		return std::tie(lhs.surname, lhs.name, lhs.patronymic) < std::tie(rhs.surname, rhs.name, rhs.patronymic);
	}

	//--------------PhoneNumber---------------

	PhoneNumber::PhoneNumber() = default;

	PhoneNumber::PhoneNumber(uint16_t country, uint16_t city, const std::string & num, std::optional<uint16_t> ext_num)
		:country_code(country), city_code(city), number(num), ext_number(ext_num)
	{}

	std::ostream& operator<<(std::ostream& out, const PhoneNumber& number)
	{
		out << '\t' << "+"s << number.country_code
			<< "("s << number.city_code
			<< ")"s << number.number;
		if (number.ext_number)
		{
			out << ""s << *number.ext_number;
		}
		return out;
	}

	bool operator==(const PhoneNumber& lhs, const PhoneNumber& rhs)
	{
		return std::tie(lhs.country_code, lhs.city_code, lhs.number, lhs.ext_number)
			== std::tie(rhs.country_code, rhs.city_code, rhs.number, rhs.ext_number);
	}

	bool operator<(const PhoneNumber& lhs, const PhoneNumber& rhs)
	{
		return std::tie(lhs.country_code, lhs.city_code, lhs.number, lhs.ext_number)
			< std::tie(rhs.country_code, rhs.city_code, rhs.number, rhs.ext_number);
	}

	//---------------Parse-------------

	Person ParsePerson(std::ifstream& in)
	{
		if (in)
		{
			in >> std::ws;
			std::string surname;
			std::string name;
			std::string patronymic;
			std::getline(in, surname, ' ');
			std::getline(in, name, ' ');
			Person person(surname, name);
			char ch = in.peek();
			if (ch != '+')
			{
				std::getline(in, patronymic, ' ');
				person.patronymic = patronymic;
			}
			return person;
		}
		return {};
	}

	PhoneNumber ParsePhonNumber(std::ifstream& in)
	{
		PhoneNumber number;
		if (in)
		{
			in >> std::ws;
			char ch;
			in >> ch;
			uint16_t country;
			in >> country;
			number.country_code = country;
			in >> ch;
			uint16_t city;
			in >> city;
			number.city_code = city;
			std::string num;
			std::getline(in, num);
			auto pos = num.find_first_of(' ');
			number.number = num.substr(1, pos);

			if (pos != std::string::npos)
			{
				auto pos_ext = num.find_first_of(pos, ' ');
				number.ext_number = std::stoi(num.substr(pos, pos_ext));
			}
		}
		return number;
	}

	//-------------------PhoneBook-------------	

	PhoneBook::PhoneBook() = default;

	PhoneBook::PhoneBook(std::ifstream& in)
	{
		if (in)
		{
			while (in)
			{
				Person person = ParsePerson(in);
				PhoneNumber number = ParsePhonNumber(in);
				if (!person.surname.empty() && !person.name.empty())
				{
					phone_book_.push_back({ person, number });
				}
			}
		}
	}

	void PhoneBook::SortByName()
	{
		std::sort(phone_book_.begin(), phone_book_.end(), [](const auto& lhs, const auto& rhs)
			{
				return lhs.first < rhs.first;
			});
	}

	void PhoneBook::SortByPhone()
	{
		std::sort(phone_book_.begin(), phone_book_.end(), [](const auto& lhs, const auto& rhs)
			{
				return lhs.second < rhs.second;
			});
	}

	std::vector<std::pair<Person, PhoneNumber>> PhoneBook::GetPhoneBook() const
	{
		return phone_book_;
	}

	std::tuple<std::string, PhoneNumber> PhoneBook::GetPhoneNumber(const std::string& surname)
	{
		auto count = std::count_if(phone_book_.begin(), phone_book_.end(), [&surname](const std::pair<Person, PhoneNumber>& pair)
			{
				return pair.first.surname == surname;
			});
		if (count == 1)
		{
			auto it = std::find_if(phone_book_.begin(), phone_book_.end(), [&surname](const std::pair<Person, PhoneNumber>& pair)
				{
					return pair.first.surname == surname;
				});
			return { ""s, it->second };
		}
		else if (count > 1)
		{
			return { "found more then 1"s, {} };
		}
		else
		{
			return { "not found"s, {} };
		}
	}

	void PhoneBook::ChangePhoneNumber(const Person& person, const PhoneNumber& number)
	{
		auto it = std::find_if(phone_book_.begin(), phone_book_.end(), [&person](const std::pair<Person, PhoneNumber>& pair)
			{
				return pair.first == person;
			});

		if (it != phone_book_.end())
		{
			it->second = number;
		}
	}

	std::ostream& operator<<(std::ostream& out, const PhoneBook& phone_book)
	{
		for (const auto& [person, number] : phone_book.GetPhoneBook())
		{
			out << person << " "s << number << std::endl;
		}
		return out;
	}

	void Dz1()
	{
		std::ifstream in("./data/phonebook.txt"s);
		PhoneBook book(in);
		std::cout << book << std::endl;
		std::cout << "------SortByName-------" << std::endl;
		book.SortByName();
		std::cout << book << std::endl;
		std::cout << "------SortByPhone-------" << std::endl;
		book.SortByPhone();
		std::cout << book << std::endl;
		std::cout << "------GetPhoneNumber-------" << std::endl;
		auto print_phone_number = [&book](const std::string& surname)
		{
			std::cout << surname << "\t";
			auto answer = book.GetPhoneNumber(surname);
			if (std::get<0>(answer).empty())
				std::cout << std::get<1>(answer);
			else
				std::cout << std::get<0>(answer);
			std::cout << std::endl;
		};
		print_phone_number("Иванов"s);
		print_phone_number("Petrov"s);
		std::cout << std::endl;
		std::cout << "------ChangePhoneNumber-------" << std::endl;
		print_phone_number("Котов"s);
		book.ChangePhoneNumber(Person{ "Котов", "Василий", "Елисееевич" },
			PhoneNumber{ 7, 123, "15344458", std::nullopt });
		print_phone_number("Котов"s);
		book.ChangePhoneNumber(Person{ "Mironova", "Margarita", "Vladimirovna" },
			PhoneNumber{ 16, 465, "9155448", 13 });
		print_phone_number("Mironova"s);
		std::cout << std::endl;
		std::cout << book;
	}
}