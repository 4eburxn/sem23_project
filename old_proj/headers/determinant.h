#ifndef __DETERMINANT_H__
#define __DETERMINANT_H__
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class Matrix
{
private:

	vector <vector<long double>> New_Matrix(vector <vector<long double>>& new_matrix, int& col);
	void DrawNewMatrix(vector<vector<long double>>& new_matrix);

public:
	int n, m;
	vector <vector<long double>> matrix;

	long double determinant(vector <vector<long double>> matrix); // ������������ �������
	Matrix operator+ (Matrix sec_matrix); // �������� ������
	Matrix operator- (Matrix sec_matrix); // �������� ������
	Matrix operator* (Matrix sec_matrix); // ��������� ������
	Matrix transposition(Matrix sm_matrix); // ���������������� �������
};

#endif // __DETERMINANT_H__