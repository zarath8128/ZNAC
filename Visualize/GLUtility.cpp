#include "GLUtility.h"
#include <cstdio>

namespace ZNAC
{
	namespace Visualize
	{
		void SetErrorCallback()
		{
			glDebugMessageCallback(ErrorNotification, 0);
			fprintf(stderr, "set error notificater code:%d\n", glGetError());
		}

		GLenum CheckError()
		{
			GLenum source, type, serverity;
			GLuint id;
			GLsizei length;
			GLchar msg_buf[256];

			GLuint check = glGetDebugMessageLog(1, 256, &source, &type, &id, &serverity, &length, msg_buf);

			if(check)
				ErrorNotification(source, type, id, serverity, length, msg_buf, 0);

			return ((check)?(type):(GL_NO_ERROR));
		}

		void APIENTRY ErrorNotification(GLenum source, GLenum type, GLuint id, GLenum serverity, GLsizei length, const GLchar *message, void *user_param)
		{
			fprintf(stderr, "\n<----  Open GL Error  ---->\n");
			fprintf(stderr, "source   :%d\n", source);
			fprintf(stderr, "type     :%d\n", type);
			fprintf(stderr, "id       :%d\n", id);
			fprintf(stderr, "serverity:%d\n", serverity);
			fprintf(stderr, "message  :%.*s\n", length, message);
			fprintf(stderr, "<----End Error Message---->\n\n");
		}
	}
}
