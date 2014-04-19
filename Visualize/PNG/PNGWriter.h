#ifndef ZNAC_VISUALIZE_PNG_PNG_WRITER_H
#define ZNAC_VISUALIZE_PNG_PNG_WRITER_H

#include <string>
#include <cstdio>
#include <cstdint>

namespace ZNAC
{
	namespace Visualize
	{
		class PNGWriter
		{
		public:
			PNGWriter(const char *dir_path, const char *file_name, uint32_t width, uint32_t height, int color_type = 6, unsigned int serial_number_width = 4, int bit_depth = 8);
			~PNGWriter();
			int operator<<(unsigned char** image);
			operator bool() const;
		private:
			std::string dir_path, file_name;
			uint32_t width, height;
			unsigned int sn_width;
			unsigned int count;
			int bit_depth, color_type;
			bool IsEnable;

			std::string FileName();
		};

		
		int PNGWrite(FILE *dest, unsigned char **image, uint32_t width, uint32_t height, int bit_depth, int color_type);
	}
}

#endif
