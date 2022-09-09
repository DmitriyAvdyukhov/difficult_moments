#pragma once
#include <iostream>
#include <optional>
#include <tuple>
#include <fstream>
#include <vector>
#include <string>


using namespace std::literals;

namespace dz1
{
	struct Person
	{
		Person();
		Person(std::string surna, std::string na, std::optional<std::string> patronym = std::nullopt);			
		std::string surname{};
		std::string name{};
		std::optional<std::string> patronymic{};
	};

	std::ostream& operator<<(std::ostream& out, const Person& person);

	bool operator==(const Person& lhs, const Person& rhs);

	bool operator<(const Person& lhs, const Person& rhs);	

	struct PhoneNumber
	{
		PhoneNumber();
		PhoneNumber(uint16_t country, uint16_t city, const std::string& num, std::optional<uint16_t> ext_num = std::nullopt);
		uint16_t country_code{};
		uint16_t city_code{};
		std::string number{};
		std::optional<uint16_t> ext_number{};
	};

	std::ostream& operator<<(std::ostream& out, const PhoneNumber& number);

	bool operator==(const PhoneNumber& lhs, const PhoneNumber& rhs);

	bool operator<(const PhoneNumber& lhs, const PhoneNumber& rhs);

	Person ParsePerson(std::ifstream& in);

	PhoneNumber ParsePhonNumber(std::ifstream& in);	

	class PhoneBook
	{
	public:
		PhoneBook();

		explicit PhoneBook(std::ifstream& in);

		void SortByName();

		void SortByPhone();

		std::vector<std::pair<Person, PhoneNumber>> GetPhoneBook() const;

		std::tuple<std::string, PhoneNumber> GetPhoneNumber(const std::string& surname);

		void ChangePhoneNumber(const Person& person, const PhoneNumber& number);

	private:
		std::vector<std::pair<Person, PhoneNumber>> phone_book_{};
	};

	std::ostream& operator<<(std::ostream& out, const PhoneBook& phone_book);

	void Dz1();
	
}// end namespace