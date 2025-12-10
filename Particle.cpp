#include "Matrices.h"

namespace Matrices
{
    Matrix::Matrix(int _rows, int _cols)
    {
        this->rows = _rows;
        this->cols = _cols;

        a.resize(rows);

        for (int i = 0; i < rows; i++)
        {
            a[i].resize(cols);

            for (int j = 0; j < cols; j++)
            {
                a[i][j] = 0;
            }
        }
    }

    Matrix operator+(const Matrix& a, const Matrix& b)
    {
        if (a.getRows() != b.getRows() || a.getCols() != b.getCols()) throw runtime_error("Error: dimensions must agree");

        Matrix c(a.getRows(), a.getCols());

        for (int i = 0; i < a.getRows(); i++)
        {
            for (int j = 0; j < a.getCols(); j++)
            {
                c(i,j) = a(i,j) + b(i,j);
            }
        }

        return c;
    }

    Matrix operator*(const Matrix& a, const Matrix& b)
    {
        if (a.getCols() != b.getRows()) throw runtime_error("Error: dimensions must agree");

        double tempSum;
        int iMax = a.getRows();
        int kMax = b.getCols();
        int jMax = a.getCols();
        Matrix c(iMax, kMax);

        for (int i = 0; i < iMax; i++)
        {
            for (int k = 0; k < kMax; k++)
            {
                tempSum = 0;

                for (int j = 0; j < jMax; j++)
                {

                    tempSum = tempSum + (a(i,j) * b(j,k));
                }
                c(i,k) = tempSum;
            }
        }
        return c;
    }

    bool operator==(const Matrix& a, const Matrix& b)
    {
        bool matching = true;

        if (a.getRows() != b.getRows() || a.getCols() != b.getCols())
        {
            matching = false;
        }
        else {

            for (int i = 0; i < a.getRows(); i++)
            {
                for (int j = 0; j < a.getCols(); j++)
                {

                    if (abs(a(i,j) - b(i,j)) > 0.001)
                    {
                        matching = false;
                        break;
                    }
                }
            }
        }
        return matching;
    }

    bool operator!=(const Matrix& a, const Matrix& b)
    {
        return !(a == b);
    }

    ostream& operator<<(ostream& os, const Matrix& a)
    {
        for (int i = 0; i < a.getRows(); i++)
        {
            for (int j = 0; j < a.getCols(); j++) 
            {
                os << setw(10) << a(i,j) << " ";
            }
            os << endl << endl;
        }

        return os;
    }

    RotationMatrix::RotationMatrix(double theta)
        : Matrix(2, 2)
    {
        a[0][0] = cos(theta);
        a[0][1] = -sin(theta);
        a[1][0] = sin(theta);
        a[1][1] = cos(theta);
    }

    ScalingMatrix::ScalingMatrix(double scale)
        : Matrix(2, 2)
    {
        a[0][0] = scale;
        a[0][1] = 0;
        a[1][0] = 0;
        a[1][1] = scale;
    }

    TranslationMatrix::TranslationMatrix(double xShift, double yShift, int nCols)
        :Matrix(2, nCols)
    {
        for ( int j = 0; j < nCols; j++)
        {
            a[0][j] = xShift;
        }

        for ( int j = 0; j < nCols; j++)
        {
            a[1][j] = yShift;
        }
    }
}
