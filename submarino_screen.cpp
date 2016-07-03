#include <stdio.h>
#include <stdlib.h>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>
#include <png.h>

#include "submarino_screen.h"

using namespace std;

Display                 *dpy;
Window                  winRoot;
GLint                   att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
XVisualInfo             *vi;
Colormap                cmap;
XSetWindowAttributes    swa;
Window                  win;
GLXContext              glc;
XWindowAttributes       gwa;
XEvent                  xev;

struct rgb BG_COLOR = {.4, .5, 1.0, 1.0};

void drawBackground() {
	glClearColor(BG_COLOR.r, BG_COLOR.g, BG_COLOR.b, BG_COLOR.alpha);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

GLuint createSubTexture() {
	FILE *fp = fopen(SUB_PATH, "rb");
	if (!fp) {
		printf("Não foi possível carregar a imagem do submarino\n");
		exit(0);
	}

	png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png_ptr) {
		png_destroy_read_struct(&png_ptr, (png_infopp) NULL, (png_infopp) NULL);
		fclose(fp);
		return TEXTURE_LOAD_ERROR;
	}

	png_infop info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr) {
		png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp) NULL);
		fclose(fp);
		return TEXTURE_LOAD_ERROR;
	}

	png_init_io(png_ptr, fp);
	png_set_sig_bytes(png_ptr, 0);
	png_read_info(png_ptr, info_ptr);
	
	int bit_depth, color_type;
	png_uint_32 twidth, theight;

	png_get_IHDR(png_ptr, info_ptr, &twidth, &theight, &bit_depth, &color_type, NULL, NULL, NULL);

	int width = twidth;
	int height = theight;

	png_read_update_info(png_ptr, info_ptr);

	int rowbytes = png_get_rowbytes(png_ptr, info_ptr);

	png_byte *image_data = new png_byte[rowbytes * height];
	if (!image_data) {
		png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp) NULL);
		fclose(fp);
		return TEXTURE_LOAD_ERROR;
	}

	png_bytep *row_pointers = new png_bytep[height];
	if (!row_pointers) {
		png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp) NULL);
		delete[] image_data;
		fclose(fp);
		return TEXTURE_LOAD_ERROR;
	}

	for (int i = 0; i < height; ++i) {
		row_pointers[height - 1 - i] = image_data + i * rowbytes;
	}

	png_read_image(png_ptr, row_pointers);

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D,0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, (GLvoid*) image_data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp) NULL);
	
	delete[] image_data;
	delete[] row_pointers;
	
	fclose(fp);

	return texture;
}

void drawSub() {
	GLuint subTexture = createSubTexture();

	glActiveTexture(GL_TEXTURE1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, subTexture);

	glBegin(GL_QUADS);
		glTexCoord2d(0.0,100); glVertex2d(100.0,100.0);
		glTexCoord2d(1.0,0.0); glVertex2d(0.0,0.0);
		glTexCoord2d(1.0,1.0); glVertex2d(0,0);
		glTexCoord2d(0.0,1.0); glVertex2d(-1.0,+1.0);
	glEnd();
}

int main(int argc, char *argv[]) {
	dpy = XOpenDisplay(NULL);
	winRoot = DefaultRootWindow(dpy);
	vi = glXChooseVisual(dpy, 0, att);

	if (vi == NULL) {
		exit(0);
	}

	cmap = XCreateColormap(dpy, winRoot, vi->visual, AllocNone);
	swa.colormap = cmap;
	swa.event_mask = ExposureMask | KeyPressMask;

	win = XCreateWindow(dpy, winRoot, 0, 0, SCREEN_W, SCREEN_H, 0, vi->depth, InputOutput, vi->visual, CWColormap | CWEventMask, &swa);
	
	XMapWindow(dpy, win);
	XStoreName(dpy, win, "Trabalho de fundamentos de SO");
	
	glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
	glXMakeCurrent(dpy, win, glc);
	glEnable(GL_DEPTH_TEST);

	drawSub();

	while(1) {
		XNextEvent(dpy, &xev);

		if(xev.type == Expose) {
			glViewport(0, 0, gwa.width, gwa.height);
			//drawBackground();
			glXSwapBuffers(dpy, win);
		}
	}
}