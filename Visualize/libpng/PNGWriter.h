#ifndef ZNAC_VISUALIZE_LIBPNG_PNG_WRITER_H
#define ZNAC_VISUALIZE_LIBPNG_PNG_WRITER_H

#include <cstdio>
#include <cstdint>
#include <png.h>
#include <GL/gl.h>

namespace ZNAC
{
	namespace libpng
	{
		//libpng wrapper function
		//written by Mmaoru OKAMOTO @ akiyama lab
		//2014/3/17
		int PNGWrite(const char *file_name, unsigned char **image, uint32_t width, uint32_t height, int bit_depth = 8, int color_type = PNG_COLOR_TYPE_RGB_ALPHA);

		//libpng wrapper function like _draw written by Pf.Masaharu NAGAYAMA
		//written by Mamoru OKAMOTO @ akiyama lab
		//2014/3/17
		//origin signature is...
		//void draw_(int p_fn, int p_Mgx, int p_Mgy, double p_dgx, p_dgy, double *p, double *q, double *r, char *image_file, char *image_dir)
		//in draw_png, p_dgx, p_dgy are deprecated. they are ignored.
		void draw_png(int count, int width, int height, double p_dgx, double p_dgy, double *r, double *g, double *b, const char *image_file, const char *image_dir);

		void GLCapture(const char *buf, int x, int y, unsigned int width, unsigned int height);

		class PNGWriter
		{
		public:
			PNGWriter(const char *file_name);
			~PNGWriter();
			int Write(unsigned char **image, uint32_t width, uint32_t height, int bit_depth = 8, int color_type = PNG_COLOR_TYPE_RGB_ALPHA);
			operator bool() const;
		private:
			FILE *dest;
			bool IsEnable;
			png_structp p_ps;
			png_infop p_pi;
		};
	}
}

#endif
