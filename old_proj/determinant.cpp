#include "headers/determinant.h"

long double Matrix::determinant(vector<vector<long double>> matrix)
{
	if (matrix.size() == 2)
		return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
	long double sum = 0;
	for (int col = 0; col < matrix.size(); col++)
	{
		//1 ���������� ����� �� 0 ������ col ������� �� num � ������������ ���������� �� det
		long double num = matrix[0][col]; long double det = 0;

		//2 ������� ����� ������� ��� ��������� ���������� ������� col ��� 0 
		vector<vector<long double>> new_matrix = matrix;
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

vector<vector<long double>> Matrix::New_Matrix(vector<vector<long double>>& new_matrix, int& col)
{
	new_matrix.erase(new_matrix.begin());
	for (int i = 0; i < new_matrix.size(); i++)
	{
		new_matrix[i].erase(new_matrix[i].begin() + col);
	}
	//DrawNewMatrix(new_matrix);
	return new_matrix;
}
void Matrix::DrawNewMatrix(vector<vector<long double>>& new_matrix)
{
	cout << endl << endl;
	for (int i = 0; i < new_matrix.size(); i++)
	{
		for (auto& el : new_matrix[i])
			cout << el << " ";
		cout << endl;
	}
}


Matrix Matrix::operator+ (Matrix sec_matrix)
{
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
	Matrix ans;
	for (int i = 0; i < n; i++)
	{
		vector <long double> nums;
		for (int j = 0; j < m; j++)
		{
			nums.push_back(matrix[i][j] - sec_matrix.matrix[i][j]);
		}
		ans.matrix.push_back(nums);
	}
	ans.n = sec_matrix.n;
	ans.m = sec_matrix.m;
	return ans;
} 

Matrix Matrix::operator* (Matrix sec_matrix)
{
	return Matrix();
} 

Matrix Matrix::transposition(Matrix sm_matrix)
{
	Matrix ans;
	for (int j = 0; j < sm_matrix.m; j++)
	{
		vector <long double> nums;
		for (int i = 0; i < sm_matrix.n; i++)
		{
			nums.push_back(sm_matrix.matrix[i][j]);
		}
		ans.matrix.push_back(nums);
	}
	ans.n = sm_matrix.m;
	ans.m = sm_matrix.n;
	return ans;
} 