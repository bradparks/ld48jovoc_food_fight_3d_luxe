#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <crtdbg.h>
#endif

#include <iostream>
#include <fstream>
#include <string>

#include <time.h>

#include <SDL.h>
#include <SDL_endian.h>

#include <GL/gl.h>
#include <GL/glu.h>

#include <il/il.h>
#include <il/ilu.h>
#include <il/ilut.h>

#include <Shape.h>

using namespace prmath;

Shape::Shape()
{
	st0 = vec2f( 0.0, 0.0 );
	st1 = vec2f( 1.0, 1.0 );
	pos = vec2f( 0, 0 );
}

Shape *Shape::simpleShape( const char *texname )
{
	Shape *shp = new Shape();

	ILuint ilImgId;
	ilGenImages( 1, &ilImgId );
	ilBindImage( ilImgId );		
	
	if (!ilLoadImage( (ILstring)texname )) {
		printf("Loading %s image failed\n", texname);
	}
	
	// Make a GL texture for it
	shp->m_texId = ilutGLBindTexImage();
	return shp;
}
	