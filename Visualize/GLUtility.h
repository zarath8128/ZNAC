#ifndef ZNAC_VISUALIZE_GLUTILITY_H
#define ZNAC_VISUALIZE_GLUTILITY_H

#include <GL/gl.h>

typedef void (APIENTRY *DEBUGPROC)(GLenum,GLenum,GLuint,GLenum,GLsizei,const GLchar *,void *);
extern "C" WINGDIAPI void APIENTRY glDebugMessageCallback(DEBUGPROC, void *);
extern "C" WINGDIAPI GLuint APIENTRY glGetDebugMessageLog(GLuint,GLsizei,GLenum*,GLenum*,GLuint*,GLenum*,GLsizei*,GLchar*);

namespace ZNAC
{
	namespace Visualize
	{
		void SetErrorCallback();
		GLenum CheckError();
		void APIENTRY ErrorNotification(GLenum source, GLenum type, GLuint id, GLenum serverity, GLsizei length, const GLchar *message, void *user_param);
	}
}


#endif
