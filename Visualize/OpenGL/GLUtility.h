#ifndef ZARATH_ZNAC_VISUALIZE_OPENGL_GLUTILITY_H
#define ZARATH_ZNAC_VISUALIZE_OPENGL_GLUTILITY_H

#include <GL/gl.h>

namespace ZNAC
{
	namespace Visualize
	{
		namespace OpenGL
		{
			/*--------Version.cpp--------*/
			class Version
			{
			public:
				unsigned int &Major, &Minor;

				Version();
				operator bool();

			private:
				unsigned int M, m;
			};

			/*--------Error.cpp--------*/
			void PrintError();
			void SetDebugMessageCallback();
		}
	}
}

#endif
