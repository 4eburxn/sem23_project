#ifndef __DETERMINANT_H__
#define __DETERMINANT_H__
#include <iostream>
#include <vector>
#include <cmath>
#include <iostream>
#include <exception>

class Matrix
{
private:
	int n;
	int m;


	std::vector <std::vector<long double>> New_Matrix(std::vector <std::vector<long double>>& new_matrix, int& col);
	void DrawNewMatrix(std::vector<std::vector<long double>>& new_matrix);
public:
	std::vector <std::vector<long double>> matrix;
	/*int n, m;
	vector <vector<long double>> matrix;*/

	bool is_broken = false;

	Matrix(int n0, int m0, std::vector <std::vector<long double>> matrix0)
	{
		if (n0 == 0 or m0 == 0){
			is_broken = true;
			std::cerr<<"������� ������ �� ����� ���� ����� 0"<<std::endl;
		}
		n = n0;
		m = m0;
		matrix = matrix0;
		
	}

	long double determinant(std::vector <std::vector<long double>> matrix); // ������������ �������
	Matrix operator+ (Matrix sec_matrix); // �������� ������
	Matrix operator- (Matrix sec_matrix); // �������� ������
	Matrix operator* (Matrix sec_matrix); // ��������� ������
	Matrix transposition(); // ���������������� �������


	std::string path_to;

	int GetN()
	{
		return n;
	}
	int GetM()
	{
		return m;
	}
	std::vector <std::vector<long double>> GetMatrix()
	{
		return matrix;
	}
};
#endif // __DETERMINANT_H__