#ifndef ZARATH_ZNAC_VISUALIZE_GLFW_CAMERA_H
#define ZARATH_ZNAC_VISUALIZE_GLFW_CAMERA_H

#include "GLFW/glfw3.h"

namespace ZNAC
{
	namespace GLFW
	{
		class Vector
		{
		public:
			double x, y, z, w;

			Vector();
			Vector(double x, double y, double z, double w);

			double &operator[](int i);
		};

		class Matrix
		{
		public:
			double a[4][4];

			Matrix();
			Matrix(double d);
			Matrix(const double a[][4]);
			Matrix(Vector v);
			Matrix(Vector *v);
			Matrix(const Matrix &m);

			static Matrix Rotate(int i, int j, double theta);

			Vector operator*(Vector v);
			Matrix operator*(Matrix m);
		};

		class Camera
		{
		public:
			Camera(GLFWwindow *window);
			Camera(int width, int height, double far, double dot_per_unit = 320);
			
			void Set();
			void Pitch(double theta);
			void Roll(double theta);
			void Yaw(double theta);
			void Zoom(double exp);
			void Distance(double exp);


		private:
			Matrix state;
			double dot_per_unit, far;
			int width, height;
		};


	}
}

#endif
