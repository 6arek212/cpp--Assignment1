#include <iostream>
#include <string>
using namespace std;

namespace ariel
{

    int **getMatrix(int rows, int cols)
    {
        int **mat = nullptr;

        mat = new int *[rows];
        for (int i = 0; i < rows; i++)
        {
            mat[i] = new int[cols];
        }

        return mat;
    }

    void fillMatrix(int **mat, int rows, int cols)
    {
        int currentCol = 0;

        for (int i = 0; i < rows && currentCol < cols; i++)
        {
            for (int j = currentCol; j < cols; j++)
            {
                mat[i][j] = i;
            }

            for (int j = i; j < rows; j++)
            {
                mat[j][currentCol] = i;
            }
            currentCol++;
        }
    }

    void fillMatrixReverse(int **mat, int rows, int cols)
    {
        int p = 0;

        for (int i = rows - 1; i >= 0 && p < cols; i--)
        {
            for (int j = cols - 1 - ((rows - 1) - i); j >= 0; j--)
            {
                mat[i][j] = p;
            }

            for (int j = i; j >= 0; j--)
            {
                mat[j][cols - 1 - ((rows - 1) - i)] = p;
            }
            p++;
        }
    }

    // void printMatrix(int **mat, int rows, int cols)
    // {
    //     for (int i = 0; i < rows; i++)
    //     {
    //         for (int j = 0; j < cols; j++)
    //         {
    //             cout << mat[i][j] << " ";
    //         }
    //         cout << endl;
    //     }
    // }

    int getMin(int x, int y)
    {
        if (x > y)
        {
            return y;
        }
        return x;
    }

    int **mergeMatrixByMin(int **mat1, int **mat2, int rows, int cols)
    {
        int **mat = getMatrix(rows, cols);

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                mat[i][j] = getMin(mat1[i][j], mat2[i][j]);
            }
        }

        return mat;
    }

    void modBy2(int **mat, int rows, int cols)
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                mat[i][j] %= 2;
            }
        }
    }

    void freeMatrix(int **mat, int rows)
    {
        for (int i = 0; i < rows; i++)
        {
            delete[] mat[i];
        }
        delete[] mat;
    }

    string mat(int cols, int rows, char sample1, char sample2)
    {
        if (cols % 2 == 0 || rows % 2 == 0)
        {
            throw invalid_argument("Mat size is always odd");
        }

        int **tempMat1 = getMatrix(rows, cols);
        int **tempMat2 = getMatrix(rows, cols);

        fillMatrix(tempMat1, rows, cols);
        fillMatrixReverse(tempMat2, rows, cols);
        int **mat = mergeMatrixByMin(tempMat1, tempMat2, rows, cols);

        freeMatrix(tempMat1, rows);
        freeMatrix(tempMat2, rows);
        modBy2(mat, rows, cols);

        string output = "";

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (mat[i][j] == 0)
                {
                    output += sample1;
                }
                else
                {
                    output += sample2;
                }
            }
            output += '\n';
        }
        freeMatrix(mat, rows);
        return output;
    }

}