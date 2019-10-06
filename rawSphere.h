

#ifndef RAWSPHERE_H_198237412734125612314872387419823
#define RAWSPHERE_H_198237412734125612314872387419823

#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>
#include <cmath>

#define M_PI 		3.14159265359f
#define M_PI_2 		M_PI/2

struct vec3
{
	float x, y, z;
	vec3(float ax, float ay, float az){x=ax; y=ay; z=az;}
	vec3 operator*(float a){x*=a; y*=a; z*=a;}
};

struct vec2
{
	float x, y;
	vec2(float ax, float ay){x=ax; y=ay;}
	vec2 operator*(float a){x*=a; y*=a;}
};

inline void push_indices(std::vector<GLushort>& indices, int sectors, int r, int s);

void createSphere(std::vector<vec3>& vertices, std::vector<GLushort>& indices, std::vector<vec2>& texcoords,
                  float radius, unsigned int rings, unsigned int sectors);


#endif//RAWSPHERE_H_198237412734125612314872387419823



