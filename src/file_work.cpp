#include "file_work.h"


void write_matrix_to_file(Matrix matrix)
{
    std::ofstream stream;
    stream.open(matrix.path_to, std::ios::binary);

    char *messege = "_Matrix__";
    stream.write(messege, sizeof("_Matrix__"));

    int sz = matrix.GetN();
    stream.write(reinterpret_cast<char *>(&sz), sizeof(int));

    int sz_2 = matrix.GetM();
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
    char *messege_new = new char[10];
    
    inf.read(messege_new, sizeof("_Matrix__"));
    messege_new[sizeof("_Matrix__")] = '\0';
    if("_Matrix__" != std::string(messege_new)){
        delete[] messege_new;
        return Matrix(0,0,std::vector<std::vector<long double>>(0));
    }
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
    delete[] messege_new;
    Matrix matrix = Matrix(sz,sz_2, V);
    return matrix;
}
