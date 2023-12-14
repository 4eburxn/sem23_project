#include "determinant.h"

long double Matrix::determinant(std::vector<std::vector<long double>> matrix_)
{
	if (n != m)
		throw std::logic_error("������������ ����� ������� ������ ��� ���������� ������");
	if (matrix_.size() == 1)
		return matrix_[0][0];
	else if (matrix_.size() == 2)
		return matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
	long double sum = 0;
	for (int col = 0; col < matrix_.size(); col++)
	{
		//1 ���������� ����� �� 0 ������ col ������� �� num � ������������ ���������� �� det
		long double num = matrix_[0][col]; long double det = 0;

		//2 ������� ����� ������� ��� ��������� ���������� ������� col ��� 0 
		std::vector<std::vector<long double>> new_matrix = matrix_;
		New_Matrix(new_matrix, col);
		
		//3 ���� ������� ������� != 2 �� ������� determinant ��� ���������� 
		int n1 = new_matrix.size();
		if (n1 > 2)
			det = determinant(new_matrix);
		else
			det = (new_matrix[0][0] * new_matrix[1][1]) - (new_matrix[0][1] * new_matrix[1][0]);
		sum += pow(-1, col) * num * det;
	}
	return sum;
}

std::vector<std::vector<long double>> Matrix::New_Matrix(std::vector<std::vector<long double>>& new_matrix, int& col)
{
	new_matrix.erase(new_matrix.begin());
	for (int i = 0; i < new_matrix.size(); i++)
	{
		new_matrix[i].erase(new_matrix[i].begin() + col);
	}
	//DrawNewMatrix(new_matrix);
	return new_matrix;
}
void Matrix::DrawNewMatrix(std::vector<std::vector<long double>>& new_matrix)
{
	std::cout << std::endl << std::endl;
	for (int i = 0; i < new_matrix.size(); i++)
	{
		for (auto& el : new_matrix[i])
			std::cout << el << " ";
		std::cout << std::endl;
	}
}


Matrix Matrix::operator+ (Matrix sec_matrix)
{
	if (n != sec_matrix.n and m != sec_matrix.m)
		throw std::logic_error("������� ������ �����������");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			sec_matrix.matrix[i][j] += matrix[i][j];
		}
	}
	return sec_matrix;
}

Matrix Matrix::operator- (Matrix sec_matrix)
{
	if (n != sec_matrix.n and m != sec_matrix.m)
		throw std::logic_error("������� ������ �����������");
	std::vector<std::vector<long double>> ans;
	for (int i = 0; i < n; i++)
	{
		std::vector <long double> nums;
		for (int j = 0; j < m; j++)
		{
			nums.push_back(matrix[i][j] - sec_matrix.matrix[i][j]);
		}
		ans.push_back(nums);
	}
	return Matrix(sec_matrix.n, sec_matrix.m, ans);
} 

Matrix Matrix::operator* (Matrix sec_matrix)
{
	if (m != sec_matrix.n)
		throw std::logic_error("wrong matrix size");
	std::vector<std::vector<long double>> new_matrix;
	/*new_matrix.n = n;
	new_matrix.m = sec_matrix.m;*/
	for (int i = 0; i < n; i++)
	{
		std::vector <long double> nums;
		for (int k = 0; k < sec_matrix.m; k++)
		{
			int sum = 0;
			for (int j = 0; j < m; j++)
			{
				sum += matrix[i][j] * sec_matrix.matrix[j][k];
			}
			nums.push_back(sum);
		}
		new_matrix.push_back(nums);
	}
	return Matrix(n, sec_matrix.m, new_matrix);
} 

Matrix Matrix::transposition()
{
	std::vector<std::vector<long double>> ans;
	for (int j = 0; j < m; j++)
	{
		std::vector <long double> nums;
		for (int i = 0; i < n; i++)
		{
			nums.push_back(matrix[i][j]);
		}
		ans.push_back(nums);
	}
	return Matrix(m, n, ans);
}