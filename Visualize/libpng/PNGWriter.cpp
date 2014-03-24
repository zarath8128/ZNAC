#include "PNGWriter.h"

using namespace ZNAC::libpng;

void FCLOSE(FILE*);

int ZNAC::libpng::PNGWrite(const char *file_name, unsigned char **image, uint32_t width, uint32_t height, int bit_depth, int color_type)
{
	FILE *dest = fopen(file_name, "wb");
	if(dest == nullptr)
	{
		fprintf(stderr, "failed open / create file : file name -> %s\n", file_name);
		return 1;
	}

	png_structp p_ps = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
	if(p_ps == nullptr)
	{
		fprintf(stderr, "failed create png_struct\n");
		FCLOSE(dest);
		return 2;
	}

	png_infop p_pi = png_create_info_struct(p_ps);
	if(p_pi == nullptr)
	{
		fprintf(stderr, "failed create png_info\n");
		png_destroy_write_struct(&p_ps, nullptr);
		FCLOSE(dest);
		return 3;
	}

	if(setjmp(p_ps->jmpbuf))
	{
		fprintf(stderr, "failed running libpng\n");
		png_destroy_write_struct(&p_ps, &p_pi);
		FCLOSE(dest);
		return 4;
	}

	png_init_io(p_ps, dest);

	png_set_IHDR(p_ps, p_pi, width, height, bit_depth, color_type, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
	png_write_info(p_ps, p_pi);
	png_write_image(p_ps, image);
	png_write_end(p_ps, p_pi);

	png_destroy_write_struct(&p_ps, &p_pi);
	FCLOSE(dest);

	return 0;
}

void ZNAC::libpng::draw_png(int count, int width, int height, double p_dgx, double p_dgy, double *r, double *g, double *b, const char *image_file, const char *image_dir)
{
	printf("count:%d width:%d height:%d\n", count, width, height);
	unsigned char *buf[height];
	for(int h = 0; h < height; ++h)
	{
		buf[h] = new unsigned char[3*width];
		for(int w = 0; w < width; ++w)
		{	
			buf[h][3*w] = r[h*width + w]*255;
			buf[h][3*w + 1] = g[h*width + w]*255;
			buf[h][3*w + 2] = b[h*width + w]*255;
		}
	}

	char path[strlen(image_file) + strlen(image_dir) + 6];
	sprintf(path, "%s/%s%04d.png", image_dir, image_file, count);

	PNGWrite(path, buf, width, height, 8, PNG_COLOR_TYPE_RGB);

	for(int h = 0; h < height; ++h)
		delete [] buf[h];
}

void GLCapture(void *buf, int x, int y, unsigned int width, unsigned int height){}

void FCLOSE(FILE *fp)
{
	if(EOF == fclose(fp))
		fprintf(stderr, "failed to close file\n");
}

PNGWriter::PNGWriter(const char *file_name):dest(fopen(file_name, "wb")), IsEnable(false)
	, p_ps(png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr)), p_pi(nullptr)
{
	if(dest == nullptr)
	{
		fprintf(stderr, "failed open / create file : file name -> %s\n", file_name);
		return;
	}

	if(p_ps == nullptr)
	{
		fprintf(stderr, "failed create png_struct\n");
		return;
	}

	p_pi = png_create_info_struct(p_ps);

	if(p_pi == nullptr)
	{
		fprintf(stderr, "failed create png_info\n");
		png_destroy_write_struct(&p_ps, nullptr);
		return;
	}

	IsEnable = true;
}

int PNGWriter::Write(unsigned char **image, uint32_t width, uint32_t height, int bit_depth, int color_type)
{
	if(!IsEnable)
		return 1;

	png_set_IHDR(p_ps, p_pi, width, height, bit_depth, color_type, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
	png_write_info(p_ps, p_pi);
	png_write_image(p_ps, image);
	return 0;
}

PNGWriter::~PNGWriter()
{
	if(dest)
		if(EOF == fclose(dest))
			fprintf(stderr, "error nt32_t width, uint32_t height, int bit_depth = 8, int color_type = PNG_COLOR_TYPE_RGB_ALPHA);at file closing\n");
	
	png_destroy_write_struct(&p_ps, &p_pi);
}

PNGWriter::operator bool()const{return IsEnable;}
