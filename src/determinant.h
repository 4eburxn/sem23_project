#ifndef __DETERMINANT_H__
#define __DETERMINANT_H__
#include <iostream>
#include <vector>
#include <cmath>


class Matrix
{
private:

	std::vector <std::vector<long double>> New_Matrix(std::vector <std::vector<long double>>& new_matrix, int& col);
	void DrawNewMatrix(std::vector<std::vector<long double>>& new_matrix);

public:
	int n, m;
	std::vector <std::vector<long double>> matrix;

	std::string path_to;

	long double determinant(std::vector <std::vector<long double>> matrix); // ������������ �������
	Matrix operator+ (Matrix sec_matrix); // �������� ������
	Matrix operator- (Matrix sec_matrix); // �������� ������
	Matrix operator* (Matrix sec_matrix); // ��������� ������
	Matrix transposition(Matrix sm_matrix); // ���������������� �������
};

#endif // __DETERMINANT_H__