#include <iostream>
#include <random>
#include <GL/gl.h>
#include <GL/glu.h>
#include "Visualize/GLFW/Window.h"
#include "basic/general.h"

using namespace ZNAC::GLFW;

struct Point2
{
	double x, y;
	Point2() = default;
	Point2(double x, double y):x(x), y(y){}
	void Draw()
	{
		glBegin(GL_POINTS);
		glVertex2d(x, y);
		glEnd();
	}
};

template<class T>
class Stack
{
public:
	Stack():buf(new T[16]), used(0), reserved(16){}
	~Stack(){delete [] buf;}
	void Push(T t){Check(); buf[used++] = t;}
	T Pop(){return buf[--used];}
	void Delete(unsigned int i){for(unsigned int j = i + 1; j < used; ++j)buf[j - 1] = buf[j];used--;}
	void Draw()
	{
		for(unsigned int i = 0; i < used; ++i)
			buf[i].Draw();
	}

	bool IsEmpty(){return used == 0;}

	T operator[](unsigned int i){return buf[i];}

//private:
	T *buf;
	unsigned int used, reserved;

	void Check()
	{
		if(used == reserved)
		{
			T *temp = new T[reserved*=2];
			for(unsigned int i = 0; i < used; ++i)
				temp[i] = buf[i];
			delete [] buf;
			buf = temp;
		}
	}
};

Stack<Point2> points;

struct Triangle
{
	unsigned int a, b, c;
	Triangle() = default;
	Triangle(unsigned int a, unsigned int b, unsigned int c):a(a), b(b), c(c){}
	void Draw()
	{
		glBegin(GL_LINE_LOOP);
		glVertex2d(points[a].x, points[a].y);
		glVertex2d(points[b].x, points[b].y);
		glVertex2d(points[c].x, points[c].y);
		glEnd();
	}
};

const unsigned int len = 100;
Stack<Triangle> triangles;
Stack<Triangle> edge;
Stack<int> done;

class tWindow
	:public Window
{
public:
	tWindow():Window()
	{
		glClearColor(1, 1, 1, 1);
	}
private:
	double *v;

	void update()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glBegin(GL_LINES);
		glColor3d(1, 0, 0);
		glVertex2d(0, -.5);
		glVertex2d(0, .5);
		glColor3d(0, 0, 1);
		glVertex2d(-.5, 0);
		glVertex2d(.5, 0);
		glEnd();
		glPointSize(3);
		glColor3d(0, 0, 0);
		points.Draw();

		glColor3d(0, 1, 0);
		triangles.Draw();

		glfwSwapBuffers(wnd);
	}
};

void rndvertex(Stack<Point2> &points, unsigned int num);
double r2(Point2 a, Point2 b);
double cr2(Point2 a, Point2 b, Point2 c);
Point2 crc(Point2 a, Point2 b, Point2 c);

template<unsigned int dim>
void DelaunaySimplexion()
{

}

int main()
{
	points.Push(Point2(-100, -100));
	points.Push(Point2(100, -100));
	points.Push(Point2(0, 100));

	rndvertex(points, len);

	for(double x = -0.8; x <= 0.8; x += .1)
	{
		points.Push(Point2(x, 0.9));
		points.Push(Point2(x, -0.9));
		points.Push(Point2(0.9, x));
		points.Push(Point2(-0.9, x));
	}

	glfwInit();
	tWindow tw;

	triangles.Push(Triangle(0, 1, 2));
	done.Push(0);
	done.Push(1);
	done.Push(2);

	while(done.used != points.used)
	{
		Stack<Triangle> ttmp, ttmp2, tres;
		Stack<unsigned int> ptmp;

		while(!triangles.IsEmpty())
		{
			Triangle t = triangles.Pop();
			if(r2(points[done.used], crc(points[t.a], points[t.b], points[t.c])) < cr2(points[t.a], points[t.b], points[t.c]))
				ttmp.Push(t);
			else
				tres.Push(t);
		}

		std::cout << "tres:" << tres.used << std::endl;

		while(!ttmp.IsEmpty())
		{
			Triangle t = ttmp.Pop();
			ttmp2.Push(Triangle(t.a, t.b, done.used));
			ttmp2.Push(Triangle(t.a, t.c, done.used));
			ttmp2.Push(Triangle(t.c, t.b, done.used));
			ptmp.Push(t.a);
			ptmp.Push(t.b);
			ptmp.Push(t.c);
		}

		while(!ttmp2.IsEmpty())
		{
			Triangle t = ttmp2.Pop();
			bool IsInvalid = false;
			double cr = cr2(points[t.a], points[t.b], points[t.c]);
			for(unsigned int j = 0; j < ptmp.used; ++j)
				if(ptmp[j] != t.a && ptmp[j] != t.b && ptmp[j] != t.c )
					IsInvalid = IsInvalid || (cr > r2(points[ptmp[j]], crc(points[t.a], points[t.b], points[t.c])));
			if(!IsInvalid)
				triangles.Push(t);
		}

		while(!tres.IsEmpty())
			triangles.Push(tres.Pop());

		done.Push(done.used);

		std::cout << triangles.used << std::endl;
	}

	for(unsigned int i = 0; i < triangles.used; ++i)
	{
		std::cout << "a:" << triangles[i].a << "\tb:" << triangles[i].b << "\tc:" << triangles[i].c << std::endl;
		for(unsigned int j = 0; j < 3; ++j)
			if(triangles[i].a == j || triangles[i].b == j || triangles[i].c == j)
			{
				triangles.Delete(i--);
				break;
			}
	}


	while(tw)
		tw.Update();



}

void rndvertex(Stack<Point2> &buf, unsigned int num)
{
	std::mt19937 rnd(0);
	std::uniform_real_distribution<double> unit(-0.85, 0.85);
	for(unsigned int i = 0; i < num; ++i)
		buf.Push(Point2(unit(rnd), unit(rnd)));
}

double r2(Point2 a, Point2 b)
{
	return (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y);
}

double cr2(Point2 a, Point2 b, Point2 c)
{
	double A = r2(b, c), B = r2(a, c), C = r2(a, b);
	return (A*B*C)/((A + B + C)*(A + B + C) - 2*(A*A + B*B + C*C));
}

Point2 crc(Point2 a, Point2 b, Point2 c)
{
	double A = r2(b, c), B = r2(a, c), C = r2(a, b);
	double P = A*(B+C - A);
	double Q = B*(A+C - B);
	double R = C*(B+A - C);
	double S = P + Q + R;
	return Point2((a.x*P + b.x*Q + c.x*R)/S, (a.y*P + b.y*Q + c.y*R)/S);
}
