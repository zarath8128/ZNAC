#include "GLUtility.h"
#include <iostream>
//#include <GL/glext.h>

namespace ZNAC
{
	namespace Visualize
	{
		namespace OpenGL
		{			        
			void PrintError()
			{       
				GLenum err = glGetError();
				if(err == GL_NO_ERROR)
				{       
					std::cerr << "-------------------------------------------\n";
					std::cerr << "glGetError returned GL_NO_ERROR.\n";
					std::cerr << "This \"does not\" invole No Problem.\n";
					std::cerr << "For example, OpenGL context not existing yet.\n";
					std::cerr << "-------------------------------------------\n";
					return;
				}

				std::cerr << "--------Error Occured--------\n";
				do      
				{       
					std::cerr << "error code:" << std::hex << err << "\n";
				}while((err = glGetError()) != GL_NO_ERROR);
				std::cerr << "-----------------------------\n";
			}

			void APIENTRY debug_message_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, void *userParam)
			{
				std::cerr << "------------Error Occured------------\n";
				std::cerr << "message from DebugMessageCallback:\n";
				std::cerr << "source  :\t" << source << "\n";
				std::cerr << "type    :\t" << type << "\n";
				std::cerr << "id      :\t" << id << "\n";
				std::cerr << "severity:\t" << severity << "\n";
				std::cerr << "message :\n" << message << "\n";
				std::cerr << "-------------------------------------\n";
			}
		}
	}
}
