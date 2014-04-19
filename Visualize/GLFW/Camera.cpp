#include "Camera.h"
#include <cmath>
#include <GL/glu.h>

using namespace ZNAC::Visualize;

Camera::Camera()
{
	eye[2] = 1;
	eye_dir[2] = -1;
	up[1] = 1;
}

void Camera::Set()
{
	gluLookAt(eye[0], eye[1], eye[2], eye[0] + eye_dir[0], eye[1] + eye_dir[1], eye[2] + eye_dir[2], up[0], up[1], up[2]);
}

void Camera::Pitch(double theta)
{
	eye_dir = Matrix::Rotate(2, 1, theta)*eye_dir;
	up = Matrix::Rotate(2, 1, theta)*up;
}

void Camera::Roll(double theta)
{
	eye_dir = Matrix::Rotate(0, 1, theta)*eye_dir;
	up = Matrix::Rotate(0, 1, theta)*up;
}

void Camera::Yaw(double theta)
{
	eye_dir = Matrix::Rotate(2, 0, theta)*eye_dir;
	up = Matrix::Rotate(2, 0, theta)*up;
}

void Camera::Shift(double x, double y, double z)
{
	eye = Matrix(Vector(x, y, z))*eye;
}

Ortho::Ortho(double width, double height, double far)
	:w(width), h(height), far(far){}

void Ortho::Set()
{
	glOrtho(-.5*w, .5*w, -.5*h, .5*h, 0, far);
}

Vector::Vector()
	:Vector(0, 0, 0, 1)
{}

Vector::Vector(double x, double y, double z, double w)
	:x(x), y(y), z(z), w(w)
{}

double &Vector::operator[](int i) 
{
	return ((i)?((i - 1)?((i - 2)?(w):(z)):(y)):(x));
}

Matrix::Matrix()
{
	for(int i = 0; i < 4; ++i)
		for(int j = 0; j < 4; ++j)
			a[i][j] = ((i == j)?(1):(0));
}

Matrix::Matrix(double d)
{
	for(int i = 0; i < 4; ++i)
		for(int j = 0; j < 4; ++j)
			a[i][j] = ((i == j)?(d):(0));
}

Matrix::Matrix(const double a[][4])
{
	for(int i = 0; i < 4; ++i)
		for(int j = 0; j < 4; ++j)
			this->a[i][j] = a[i][j];
}

Matrix::Matrix(Vector v)
{
	for(int i = 0; i < 4; ++i)
		for(int j = 0; j < 4; ++j)
			a[i][j] = ((j == 3)?(v[i]):((i == j)?(1):(0)));
}

Matrix::Matrix(Vector *v)
{
	for(int i = 0; i < 4; ++i)
		for(int j = 0; j < 4; ++j)
			a[i][j] = v[i][j];
}

Matrix::Matrix(const Matrix &m)
{
	for(int i = 0; i < 4; ++i)
		for(int j = 0; j < 4; ++j)
			a[i][j] = m.a[i][j];
}

Matrix Matrix::Rotate(int i, int j, double theta)
{
	Matrix ret;
	ret.a[i][i] = cos(theta);
	ret.a[i][j] = sin(theta);
	ret.a[j][i] = -sin(theta);
	ret.a[j][j] = cos(theta);
	return ret;
}

Vector Matrix::operator*(Vector v)
{
	return Vector
		(
		 a[0][0]*v[0] + a[0][1]*v[1]+a[0][2]*v[2]+a[0][3]*v[3],
		 a[1][0]*v[0] + a[1][1]*v[1]+a[1][2]*v[2]+a[1][3]*v[3],
		 a[2][0]*v[0] + a[2][1]*v[1]+a[2][2]*v[2]+a[2][3]*v[3],
		 a[3][0]*v[0] + a[3][1]*v[1]+a[3][2]*v[2]+a[3][3]*v[3]
		 );
}

Matrix Matrix::operator*(Matrix m)
{
	Matrix ret;
	for(int r = 0; r < 4; ++r)
		for(int c = 0; c < 4; ++c)
		{
			ret.a[r][c] = 0;
			for(int k = 0; k < 4; ++k)
				ret.a[r][c] += a[r][k]*m.a[k][c];
		}
	return ret;
}
