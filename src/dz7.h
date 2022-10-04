#pragma once
#include "person.pb.h"
#include <vector>
#include <string>
#include <optional>
#include <sstream>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <utility>
#include <cassert>

namespace students_group
{
	using Path = std::filesystem::path;

	struct FullName
	{
		std::string name{};
		std::string surname{};
		std::optional<std::string> patronymic{};
	};

	bool operator==(const FullName& lhs, const FullName& rhs)
	{
		return lhs.name == rhs.name && lhs.surname == rhs.surname && lhs.patronymic == rhs.patronymic;
	}

	std::ostream& operator<<(std::ostream& out, const FullName& name)
	{
		out << name.surname << " " << name.name << " ";
		if (name.patronymic)
		{
			out << name.patronymic.value() << " ";
		}		
		return out;
	}

	struct Student
	{
		Student() = default;
		explicit Student(const FullName& n, std::vector<int> ev)
			: name(n), evalutions(ev)
		{
			auto sum = std::accumulate(evalutions.begin(), evalutions.end(), 0) * 1.0;
			average_rating =  sum / evalutions.size() * 1.;
		}

		void AddEvalution(int eval)
		{
			evalutions.push_back(eval);
			auto sum = std::accumulate(evalutions.begin(), evalutions.end(), 0) * 1.0;
			average_rating = sum / evalutions.size() * 1.;
		}
		FullName name{};
		std::vector<int> evalutions{};
		double average_rating{ 0. };
	};

	std::ostream& operator<<(std::ostream& out, const Student& student)
	{
		out << student.name << " " << student.average_rating << " ";
		if (student.evalutions.size())
		{
			for (int n : student.evalutions)
			{
				out << n << " ";
			}
		}
		out << std::endl;
		return out;
	}

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

		explicit StudentsGroup(const std::string& path)
			: to_file_(path)
		{}

		void AddPath(const std::string& path)
		{
			to_file_ = path;
		}

		void AddStudent(const Student& student)
		{
			students_.push_back(student);
		}

		void Open() override
		{
			std::ifstream in(to_file_, std::ios::binary);
			students_group_proto::SyudentGroup students_proto;
			if (students_proto.ParseFromIstream(&in))
			{				
				for (const auto& student_proto : students_proto.students_proto())
				{						
					students_group_proto::FullName full_name_proto = student_proto.name_proto();
					FullName full_name;
					full_name.name = full_name_proto.name_proto();
					full_name.surname = full_name_proto.surname_proto();
					if (full_name_proto.patronymic_proto().size())
					{
						full_name.patronymic = full_name_proto.patronymic_proto();
					}	
					Student student;
					student.name = std::move(full_name);
					student.average_rating = student_proto.average_rating_proto();
					for (auto n : student_proto.evalutions_proto())
					{
						student.evalutions.push_back(std::move(n));
					}
					students_.push_back(std::move(student));
				}
			}
		}

		void Save() override
		{
			students_group_proto::SyudentGroup students_proto;			
			
			for (const auto& student : students_)
			{
				students_group_proto::Student student_proto;
				student_proto.set_average_rating_proto(student.average_rating);
				student_proto.mutable_name_proto()->set_name_proto(student.name.name);
				student_proto.mutable_name_proto()->set_surname_proto(student.name.surname);
				if (student.name.patronymic.has_value())
				{
					student_proto.mutable_name_proto()->set_patronymic_proto(student.name.patronymic.value());
				}				
				for (int n : student.evalutions)
				{
					student_proto.add_evalutions_proto(n);
				}
				
				students_proto.mutable_students_proto()->Add(std::move(student_proto));
			}
			std::ofstream out(to_file_, std::ios::binary);
			if (out)
			{
				students_proto.SerializePartialToOstream(&out);
			}
		}

		std::optional<Student> FindStudent(const FullName& name) const
		{
			if (auto it = std::find_if(students_.begin(), students_.end(), [&](const Student& student)
				{
					return student.name == name;
				});
				it != students_.end())
			{
				return *it;
			}
				return std::nullopt;			
		}

		double GetAverageScore(const FullName& name) override
		{
			auto student = FindStudent(name);
			if (student.has_value())
			{
				return student.value().average_rating;
			}
		}

		std::string GetAllInfo(const FullName& name) override
		{
			auto student = FindStudent(name);
			if (student.has_value())
			{
				std::stringstream str;
				str << student.value();
				return str.str();
			}
			return {};
		}

		std::string GetAllInfo() override
		{
			std::stringstream str;
			for (const auto& student : students_)
			{
				str << student;
			}
			return str.str();
		}

	private:
		Path to_file_;
		std::vector<Student> students_;
	};
}

namespace dz7
{
	void TestStudentsGroup()
	{
		std::cout << "Test serialization students group" << std::endl;
		students_group::StudentsGroup students;
		students_group::Student st1{ {"Ivanov", "Ivan"}, {5, 5, 4, 3} };
		students.AddStudent(std::move (st1));
		students_group::Student st2{ {"Ivanova", "Alisa"}, {5, 5, 4, 5} };
		students.AddStudent(std::move(st2));
		students_group::Student st3{ {"Ivanov", "Ivan", "Petrovich"}, {5, 5, 4, 5, 3} };
		students.AddStudent(std::move(st3));
		students_group::Student st4{ {"Ivanov", "Alisa", "Petrovna"}, {5, 4, 4, 3} };
		students.AddStudent(std::move(st4));		
		std::cout << students.GetAllInfo() << std::endl;

		assert(students.GetAverageScore({ "Ivanov", "Ivan" }) == 4.25);
		students.AddPath("file");
		students.Save();

		students_group::StudentsGroup students1("file");
		students1.Open();
		std::cout << students1.GetAllInfo() << std::endl;
		assert(students1.GetAverageScore({ "Ivanov", "Ivan" }) == 4.25);
		assert(students1.GetAverageScore({ "Ivanov", "Ivan" }) == students.GetAverageScore({ "Ivanov", "Ivan" }));
		assert(students1.GetAllInfo({ "Ivanov", "Ivan" }) == students.GetAllInfo({ "Ivanov", "Ivan" }));
		assert(students.GetAllInfo() == students1.GetAllInfo());
		std::cout << "Test serialization students group is Ok" << std::endl;
	}

	void Dz7()
	{
		TestStudentsGroup();
	}
}