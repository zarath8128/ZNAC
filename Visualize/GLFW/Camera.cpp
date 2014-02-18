#include "Camera.h"
#include <cmath>
#include <GL/glu.h>

using namespace ZNAC::GLFW;

Camera::Camera(GLFWwindow *window)
	:dot_per_unit(320), far(100)
{
	glfwGetWindowSize(window, &width, &height);
}

Camera::Camera(int width, int height, double far, double dpu)
	:width(width), height(height), far(far), dot_per_unit(dpu)
{}

void Camera::Set()
{
	glOrtho(state.a[0][3]-width/dot_per_unit, state.a[0][3]+width/dot_per_unit, state.a[1][3] - height/dot_per_unit, state.a[1][3] + height/dot_per_unit, 0, far);
	gluLookAt(state.a[0][0], state.a[1][0], state.a[2][0], state.a[0][3], state.a[1][3], state.a[2][3], state.a[0][1], state.a[1][1], state.a[2][1]);
}

void Camera::Pitch(double theta)
{
	state = state*Matrix::Rotate(0, 1, theta);
}

void Camera::Roll(double theta)
{
	state = state*Matrix::Rotate(1, 2, theta);
}

void Camera::Yaw(double theta)
{
	state = state*Matrix::Rotate(0, 2, theta);
}

void Camera::Zoom(double e)
{
	dot_per_unit *= exp(-e);
}

void Camera::Distance(double d)
{
	state = state*Matrix(exp(d));
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
			a[i][j] = ((i == 3)?(v[j]):((i == j)?(1):(0)));
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
