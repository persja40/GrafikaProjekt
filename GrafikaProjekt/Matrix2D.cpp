#include "Matrix2D.h"



Matrix2D::Matrix2D()
{
	matrixArray = new float[9];
	for (int i = 0; i < 9; i++) matrixArray[i] = 0;
}


Matrix2D::~Matrix2D()
{
	delete[] matrixArray;
}

void Matrix2D::fillWithIdentity()
{
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			setElement(i, j, i == j ? 1 : 0);
		}
	}
}

inline float Matrix2D::getElement(int row, int column) const
{
	return matrixArray[row*3+column];
}

inline void Matrix2D::setElement(int row, int column, float value)
{
	matrixArray[row * 3 + column] = value;
}

Matrix2D  Matrix2D::operator*(const Matrix2D & secondMatrix) const
{
	Matrix2D result;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			result.setElement(i, j, 0);
		}
	}

	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			for (int k = 0; k < 3; k++){
				result.setElement(i, j, result.getElement(i, j) + getElement(i, k)*secondMatrix.getElement(k, j));
			}
		}
	}

	return result;
}

Matrix2D & Matrix2D::operator=(const Matrix2D & secondMatix)
{
	this->matrixArray  = secondMatix.getMatrixArrayCopy();
	return *this;
}

Matrix2D::Matrix2D(const Matrix2D & source)
{
	matrixArray = source.getMatrixArrayCopy();
}

float * Matrix2D::getMatrixArrayCopy() const
{
	float * copy = new float[9];
	return (float *) memcpy(copy, matrixArray, sizeof(float) * 9);
}

float ** Matrix2D::getMatrixCopyIn2DForm() const
{
	float ** copy= new float * [3];
	for (int i = 0; i < 3; i++) {
		copy[i] = (float *) memcpy(new float(3), matrixArray + 3 * i, 3 * sizeof(float));
	}

	return copy;
}

void Matrix2D::printMatrix()
{
	for (int i = 0; i < 9; i++) {
		std::cout << matrixArray[i] << '\t';
		if ((i + 4) % 3 == 0) {
			std::cout << std::endl;
		}
	}
	std::cout << std::endl;
}

Matrix2D Matrix2D::getRotationMatrix(float angle)
{
	Matrix2D rotationMatrix;
	rotationMatrix.setElement(0, 0,cos(angle));
	rotationMatrix.setElement(1, 1, cos(angle));
	rotationMatrix.setElement(0, 1, -sin(angle));
	rotationMatrix.setElement(1, 0, sin(angle));
	rotationMatrix.setElement(2, 2, 1);

	return rotationMatrix;
}

Matrix2D Matrix2D::getTranslationMatrix(float tx, float ty)
{
	Matrix2D translationMatrix;

	translationMatrix.fillWithIdentity();
	translationMatrix.setElement(0, 2, tx);
	translationMatrix.setElement(1, 2, ty);

	return translationMatrix;
}

Matrix2D Matrix2D::getScaleMatrix(float sx, float sy)
{
	Matrix2D scaleMatrix;

	scaleMatrix.setElement(2, 2, 1);
	scaleMatrix.setElement(1, 1, sy);
	scaleMatrix.setElement(0, 0, sx);
	return scaleMatrix;
}


