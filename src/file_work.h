#ifndef __FILE_WORK_H__
#define __FILE_WORK_H__ 1

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include"determinant.h"

void write_matrix_to_file(Matrix matrix);
Matrix read_matrix_from_file(std::string path);

#endif // __FILE_WORK_H__