
/////////////////////////////////////////////////////// cubemap.h /////////////////////////////////////

#ifndef CUBEMAP_H_182374891723541238491723894712
#define CUBEMAP_H_182374891723541238491723894712



#include <gl/gl.h>			// original 001
#include <gl/glu.h>			// original 001
#include "opengl.h"
extern "C"{
#include "stbi.h"
}
void create_cube_map(
					 const char* front,
					 const char* back,
					 const char* top,
					 const char* bottom,
					 const char* left,
					 const char* right,
					 GLuint* tex_cube
					);
bool load_cube_map_side(GLuint texture, GLenum side_target, const char* file_name);







#endif//CUBEMAP_H_182374891723541238491723894712


