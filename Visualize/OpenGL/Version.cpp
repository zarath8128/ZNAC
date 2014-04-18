#include <GL/gl.h>
#include <iostream>
#include "GLUtility.h"

namespace ZNAC
{
	namespace Visualize
	{
		namespace OpenGL
		{
			Version::Version():Major(M), Minor(m), M(0), m(0)
			{
				const char *ver;
				if(!(ver = (const char *)glGetString(GL_VERSION)))
				{
					std::cerr << "glGetString failed.\n";
					PrintError();
					return;
				}

				M = ver[0] - '0';
				m = ver[2] - '0';
			}

			Version::operator bool(){return M != 0;}
		}
	}
}
