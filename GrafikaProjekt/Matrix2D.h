#pragma once
#include <math.h>
#include <cstring>
#include <iostream>

class Matrix2D
{
private:
	float * matrixArray;
public:
	Matrix2D();
	~Matrix2D();
	void fillWithIdentity();
	inline float getElement(int row, int column) const;
	inline void setElement(int row, int column, float value);
	Matrix2D  operator * (const Matrix2D & secondMatrix) const;
	Matrix2D & operator = (const Matrix2D & secondMatix);
	Matrix2D(const Matrix2D & source);

	float * getMatrixArrayCopy() const;
	float ** getMatrixCopyIn2DForm() const;

	void printMatrix();

	static Matrix2D getRotationMatrix(float angle) ;
	static Matrix2D getTranslationMatrix(float tx, float ty) ;
	static Matrix2D getScaleMatrix(float sx, float sy) ; 
};

