#include <iostream>
#include <string>
#include <vector>
#include "mat.hpp"
using namespace std;

namespace ariel
{
    void fillMatrix(vector<vector<int>> &mat, int rows, int cols)
    {
        /*
            0000
            0111
            0122
            0123
        */
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

    void fillMatrixReverse(vector<vector<int>> &mat, int rows, int cols)
    {

        /*
            3210
            2210
            1110
            0000
        */

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

    void printMatrix(vector<vector<int>> &mat, int rows, int cols)
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                cout << mat[i][j] << " ";
            }
            cout << endl;
        }
    }

    int getMin(int x, int y)
    {
        if (x > y)
        {
            return y;
        }
        return x;
    }

    vector<vector<int>> mergeMatrixByMin(vector<vector<int>> &mat1, vector<vector<int>> &mat2, int rows, int cols)
    {
        vector<vector<int>> mat(rows, vector<int>(cols));

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                mat[i][j] = getMin(mat1[i][j], mat2[i][j]);
            }
        }

        return mat;
    }

    void modBy2(vector<vector<int>> &mat, int rows, int cols)
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                mat[i][j] %= 2;
            }
        }
    }

    bool isValidSimple(char sample)
    {
        return !(sample < simMin || sample > simMax);
    }

    string toString(vector<vector<int>> mat, int rows, int cols, char sample1, char sample2)
    {
        string output;

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
        return output;
    }

    string mat(int cols, int rows, char sample1, char sample2)
    {

        if (!isValidSimple(sample1) || !isValidSimple(sample2))
        {
            throw invalid_argument("Invaild sample");
        }

        if (cols < 0 || rows < 0)
        {
            throw invalid_argument("Cols & Rows cant be negative values");
        }

        if (cols % 2 == 0 || rows % 2 == 0 || cols < 0 || rows < 0)
        {
            throw invalid_argument("Mat size is always odd");
        }

        vector<vector<int>> tempMat1(rows, vector<int>(cols));
        vector<vector<int>> tempMat2(rows, vector<int>(cols));

        fillMatrix(tempMat1, rows, cols);
        fillMatrixReverse(tempMat2, rows, cols);

        vector<vector<int>> mat = mergeMatrixByMin(tempMat1, tempMat2, rows, cols);
        modBy2(mat, rows, cols);
        return toString(mat, rows, cols, sample1, sample2);
    }

}