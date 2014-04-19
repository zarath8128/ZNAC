#ifndef ZARATH_ZNAC_VISUALIZE_GLFW_CAMERA_H
#define ZARATH_ZNAC_VISUALIZE_GLFW_CAMERA_H

#include "GLFW/glfw3.h"
#include "Joystick.h"

namespace ZNAC
{
	namespace Visualize
	{
		class Vector
		{
		public:
			double x, y, z, w;

			Vector();
			Vector(double x, double y, double z, double w = 1);

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
			Camera();
			
			void Set();
			void Pitch(double theta);
			void Roll(double theta);
			void Yaw(double theta);
			void Shift(double x, double y, double z);

		private:
			Vector eye;
			Vector eye_dir;
			Vector up;
		};

		class Projection
		{
		public:
			virtual void Set() = 0;
		};

		class Ortho
			:public Projection
		{
		public:
			Ortho(double width, double height, double far = 100);
			void Set();
		private:
			double w, h, far;
		};
	}
}

#endif
