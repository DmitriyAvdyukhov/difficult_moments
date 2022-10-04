#pragma once
#include <vector>
#include <string>
#include <optional>
#include <sstream>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <utility>
#include <cassert>
#include <numeric>
#include <gtest/gtest.h>


namespace students_group
{
	using Path = std::filesystem::path;

	struct FullName
	{
		std::string name{};
		std::string surname{};
		std::optional<std::string> patronymic{};
	};

	bool operator==(const FullName& lhs, const FullName& rhs);	

	std::ostream& operator<<(std::ostream& out, const FullName& name);	

	struct Student
	{
		Student() = default;

		explicit Student(const FullName& n, std::vector<int> ev);		

		void AddEvalution(int eval);
		
		FullName name{};
		std::vector<int> evalutions{};
		double average_rating{ 0. };
	};

	std::ostream& operator<<(std::ostream& out, const Student& student);
	
	class IRepository
	{
	public:
		virtual void Open() = 0; // бинарная десериализация в файл
		virtual void Save() = 0; // бинарная сериализация в файл
	};

	class IMethods
	{
	public:
		virtual double GetAverageScore(const FullName& name) = 0;
		virtual std::string GetAllInfo(const FullName& name) = 0;
		virtual std::string GetAllInfo() = 0;
	};

	class StudentsGroup final : public IRepository, public IMethods
	{
	public:
		StudentsGroup() = default;

		explicit StudentsGroup(const std::string& path);			

		void AddPath(const std::string& path);		

		void AddStudent(const Student& student);		

		void Open() override;		

		void Save() override;		

		std::optional<Student> FindStudent(const FullName& name) const;		

		double GetAverageScore(const FullName& name) override;		

		std::string GetAllInfo(const FullName& name) override;		

		std::string GetAllInfo() override;		

	private:
		Path to_file_;
		std::vector<Student> students_;
	};
}

namespace dz7
{
	void TestStudentsGroup();	

	void Dz7();	
}