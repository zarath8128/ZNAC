#ifndef ZARATH_ZNAC_VISUALIZE_SCREEN_H
#define ZARATH_ZNAC_VISUALIZE_SCREEN_H

#include <GL/gl.h>

namespace ZNAC
{
	namespace Visualize
	{
		//for off screen rendering using only opengl.
		class Screen
		{
		public:
			Screen();

		private:
			GLuint color, depth;
		};
	}
}

#endif
