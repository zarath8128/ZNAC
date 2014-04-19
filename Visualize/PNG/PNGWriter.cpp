#include "PNGWriter.h"
#include <png.h>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <cerrno>

namespace ZNAC
{
	namespace Visualize
	{

		PNGWriter::PNGWriter(const char *dir_path, const char *file_name, uint32_t width, uint32_t height, int color_type, unsigned int serial_number_width, int bit_depth)
			:dir_path(dir_path), file_name(file_name), width(width), height(height), sn_width(serial_number_width), count(0), bit_depth(bit_depth), color_type(color_type), IsEnable(true){}

		PNGWriter::~PNGWriter(){}

		int PNGWriter::operator<<(unsigned char** image)
		{
			int err;
			FILE *dest = fopen(FileName().c_str(), "wb");
			if(!dest)
			{
				err = errno;
				std::cerr << "----------------------------------\n";
				std::cerr << "failed opening file " << FileName() << "\n";
				std::cerr << "errno:" << err << "\n";
				std::cerr << "description is below:\n\n";
				std::cerr << strerror(err);
				std::cerr << "\n";
				std::cerr << "----------------------------------\n";
				return err;
			}

			if((err = PNGWrite(dest, image, width, height, bit_depth, color_type)))
			{
				std::cerr << "failed writing out png file.\n";
				return err;
			}

			count++;

			if(fclose(dest))
			{
				int err = errno;
				std::cerr << "----------------------------------\n";
				std::cerr << "failed closing file " << FileName() << "\n";
				std::cerr << "errno:" << err << "\n";
				std::cerr << "description is below:\n\n";
				std::cerr << strerror(err);
				std::cerr << "\n";
				std::cerr << "----------------------------------\n";
				return err;
			}
			return 0;
		}

		std::string PNGWriter::FileName()
		{
			std::ostringstream tmp;
			tmp << dir_path << "/" << file_name << std::setw(sn_width) << std::setfill('0') << count << ".png";
			return tmp.str();
		}

		PNGWriter::operator bool() const{return IsEnable;}

		int PNGWrite(FILE *dest, unsigned char **image, uint32_t width, uint32_t height, int bit_depth, int color_type)
		{
			png_structp p_ps = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
			if(p_ps == nullptr)
			{
				fprintf(stderr, "failed create png_struct\n");
				return -1;
			}

			png_infop p_pi = png_create_info_struct(p_ps);
			if(p_pi == nullptr)
			{
				fprintf(stderr, "failed create png_info\n");
				png_destroy_write_struct(&p_ps, nullptr);
				return -2;
			}
	
			if(setjmp(p_ps->jmpbuf))
			{
				std::cerr << "failed running libpng\n";
				return -3;
			}

			png_init_io(p_ps, dest);

			png_set_IHDR(p_ps, p_pi, width, height, bit_depth, color_type, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
			png_write_info(p_ps, p_pi);
			png_write_image(p_ps, image);
			png_write_end(p_ps, p_pi);

			png_destroy_write_struct(&p_ps, &p_pi);

			return 0;
		}
	}
}
