#include "file_work.h"


void write_matrix_to_file(Matrix matrix)
{
    std::ofstream stream;
    stream.open(matrix.path_to, std::ios::binary);

    int sz = matrix.n;
    stream.write(reinterpret_cast<char *>(&sz), sizeof(int));

    int sz_2 = matrix.m;
    stream.write(reinterpret_cast<char *>(&sz_2), sizeof(int));

    for (int i = 0; i < sz; ++i)
    {
        std::vector<long double> &v = matrix.matrix[i];

        for (int j = 0; j < sz_2; ++j)
        {
            long double n = v[j];
            stream.write(reinterpret_cast<char *>(&n), sizeof(long double));
        }
    }
    stream.close();
}

Matrix read_matrix_from_file(std::string path)
{
    std::ifstream inf;
    inf.open(path, std::ios::binary);

    int sz;
    inf.read(reinterpret_cast<char *>(&sz), sizeof(int));
    int sz_2;
    inf.read(reinterpret_cast<char *>(&sz_2), sizeof(int));
    std::vector<std::vector<long double>> V;
    for (int i = 0; i < sz; ++i)
    {
        std::vector<long double> v;
        for (int j = 0; j < sz_2; ++j)
        {
            long double n;
            inf.read(reinterpret_cast<char *>(&n), sizeof(long double));
            v.push_back(n);
        }
        V.emplace_back(v);
    }

    Matrix matrix;
    matrix.matrix = std::vector<std::vector<long double>>(V);
    matrix.n = sz;
    matrix.m = sz_2;
    inf.close();
    matrix.path_to = path;
    return matrix;
}
