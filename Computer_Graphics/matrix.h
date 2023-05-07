#ifndef MATRIX_H
#define MATRIX_H

#include <array>
#include <iostream>

template <int Rows, int Cols>
class Matrix
{
public:
    template <typename... Args>
    Matrix(Args... args) : data{ { args... } } {}

    double& operator()(int row, int col) {
        return data[row][col];
    }

    double operator()(int row, int col) const {
        return data[row][col];
    }

    Matrix<3, 1> operator*(const Matrix<3, 1>& mat) const {
            Matrix<3, 1> result{};

            for (int i = 0; i < 3; ++i) {
                double sum = 0.0;
                for (int j = 0; j < 3; ++j) {
                    sum += (*this)(i, j) * mat(j, 0);
                }
                result(i, 0) = sum;
            }

            return result;
    }

    Matrix<3, 3> operator*(const Matrix<3, 3>& mat) const {
        Matrix<3, 3> result;

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                double sum = 0.0;
                for (int k = 0; k < 3; ++k) {
                    sum += (*this)(i, k) * mat(k, j);
                }
                result(i, j) = sum;
            }
        }

        return result;
    }

    Matrix<3, 3> negate() {
        Matrix<3, 3> result;
        result = (*this);
        result(0, 2) = -(*this)(0, 2);
        result(1, 2) = -(*this)(1, 2);

        return result;
    }

    Matrix<3, 3> to_3x3() {
        return {1.0, 0.0, (*this)(0, 0),
                0.0, 1.0, (*this)(1, 0),
                0.0, 0.0, 1};
    }

    QPointF get_coords() {
        QPointF point(data[0][0], data[1][0]);
        return point;
    }

    void printMatrix() {
        for (int i = 0; i < Rows; ++i) {
            for (int j = 0; j < Cols; ++j) {
                std::cout << (*this)(i, j) << " ";
            }
            std::cout << "\n";
        }
    }

private:
    std::array<std::array<double, Cols>, Rows> data;
};

#endif // MATRIX_H
