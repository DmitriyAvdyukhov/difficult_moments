#pragma once
#include <cassert>
#include <list>
#include <vector>
#include <iostream>
#include <math.h>
#include <sstream>

namespace dz3
{
	void AddNumberList(std::list<double>& list)
	{
		double sum = 0.;
		for (const auto& l : list)
		{
			sum += l;
		}
		list.push_back(sum / list.size());
	}

	void TestList()
	{
		std::cout << "Test List" << std::endl;
		std::list<double>list{ 20., 10.5, 3.5 };
		AddNumberList(list);
		assert(list.back() == 11.333333333333334);
		AddNumberList(list);
		assert(list.back() == 11.333333333333334);
		std::cout << "Test List is Ok" << std::endl;
	}

	class Matrix
	{
	public:
		Matrix(int n)
		{
			matrix_.resize(n);
			for (int i = 0; i < n; ++i)
			{
				matrix_[i].resize(n);				
			}
		}

		void FillMatrix()
		{
			std::cout << "Enter first line of matrix" << std::endl;
			bool is_first = false;
			for (auto& mat : matrix_)
			{
				if (is_first)
				{
					std::cout << "Enter next line of matrix" << std::endl;
				}
				is_first = true;
				for (auto& m : mat)
				{
					std::cout << "Enter your number: ";
					std::cin >> m;					
				}	
				std::cout << std::endl;
			}
		}

		void Print() const
		{
			for (const auto& mat : matrix_)
			{
				for (const auto& m : mat)
				{
					std::cout << m << " ";
				}
				std::cout << std::endl;
			}
		}

		double Determinant(const std::vector<std::vector<double>>& matrix, int n)
		{
			if (n == 0)
			{
				return 0.;
			}
			double result = 0.;
			if (n == 1)
			{
				return matrix[0][0];
			}
			else if (n == 2)
			{
				return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
			}
			else
			{
				std::vector<std::vector<double>>mat;
				mat.resize(n - 1);
				for (auto& m : mat)
				{
					m.resize(n - 1);
				}

				for (int i = 0; i < n; ++i)
				{
					int a = 0;
					for (int k = 1; k < n; ++k)
					{
						int b = 0;
						for (int s = 0; s < n; ++s)
						{
							if (s != i)
							{
								mat[a][b] = matrix[k][s];
								++b;
							}
						}
						++a;
					}
					result += pow(-1, static_cast<double>(i)) * matrix[0][i] * Determinant(mat, n - 1);
				}
				
			}		
				return result;
		};

		std::vector<std::vector<double>> GetMatrix() const
		{
			return matrix_;
		}
		int Size() const
		{
			return matrix_.size();
		}
	private:
		std::vector<std::vector<double>> matrix_;
	};

	void TestMatrix()
	{
		std::cout << "Test determant matrix" << std::endl;
		int count = 0;
		std::cout << "Enter the bit depth of the matrix : ";
		std::cin >> count;
		Matrix matrix(count);
		matrix.FillMatrix();
		matrix.Print();
		std::cout << "Matrix determenant equel = " << matrix.Determinant(matrix.GetMatrix(), matrix.Size()) << std::endl;
		std::cout << "Test determant matrix is Ok" << std::endl;
	}

	template<typename T>
	class Iterator
	{
	public:
		Iterator() = default;
		Iterator(T& value)
			:ptr_(&value)
		{}

		void operator++()
		{
			  ptr_++;
		}		

		void operator--()
		{
			 ptr_--;
		}

		void operator++(int)
		{
			++ptr_;
		}

		void operator--(int)
		{
			 --ptr_;
		}

		T& operator*()
		{
			return *ptr_;
		}

		T& operator->()
		{
			return*ptr_;
		}

		T& operator*() const
		{
			return *ptr_;
		}

		T& operator->() const
		{
			return*ptr_;
		}

	private:
		T* ptr_ = nullptr;
	};

	void TestIterator()
	{
		std::cout << "Test Iterator" << std::endl;
		std::vector<int> vec{ 1, 2, 3, 4, 5, 6 };
		std::stringstream str;
		for (const Iterator<int>& v : vec)
		{
			str << *v <<" ";
		}	
		assert(str.str() == "1 2 3 4 5 6 ");
		Iterator it{ vec[0] };		
		++it;	
		assert(2 == *it);
		it++;
		assert(3 == *it);
		--it;
		assert(2 == *it);
		it--;
		assert(1 == *it);
		std::cout << "Test Iterator is Ok" << std::endl;
	}

	void Dz3()
	{
		TestList();
		TestMatrix();
		TestIterator();
	}
}