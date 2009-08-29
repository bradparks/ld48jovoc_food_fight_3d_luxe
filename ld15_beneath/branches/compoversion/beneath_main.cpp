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

// local includes
#include <tweakval.h>
#include <gamefontgl.h>

using namespace std;

// 30 ticks per sim frame
#define STEPTIME (33)

//============================================================================
void errorMessage( std::string msg )
{
	// todo: on linux or other OS, just printf
	MessageBoxA( NULL, msg.c_str(), "ld15_beneath ERROR", MB_OK | MB_ICONSTOP );
}

//============================================================================
int main( int argc, char *argv[] )
{	

	// I can't live without my precious printf's
#ifndef NDEBUG
	AllocConsole();
	SetConsoleTitle( L"ld15_beneath CONSOLE" );
	freopen("CONOUT$", "w", stdout );
#endif

	// Initialize SDL
	if (SDL_Init( SDL_INIT_NOPARACHUTE | SDL_INIT_VIDEO ) < 0 ) 
	{
		errorMessage( string("Unable to init SDL:") + SDL_GetError() );
		exit(1);
	}

	// cheezy check for fullscreen
	Uint32 mode_flags = SDL_OPENGL;
	for (int i=1; i < argc; i++)
	{
		if (!stricmp( argv[i], "-fullscreen"))
		{
			mode_flags |= SDL_FULLSCREEN;
		}
	}

	if (SDL_SetVideoMode( 800, 600, 32, mode_flags ) == 0 ) 
	{
		errorMessage( string("Unable to set video mode: ") +  SDL_GetError() ) ;
		exit(1);
	}
		

	SDL_WM_SetCaption( "LD15 Beneath", NULL );

	// seed rand
	srand( time(0) );

	// initialize DevIL
	ilInit();
	ilutRenderer( ILUT_OPENGL );

	//=====[ Main loop ]======
	Uint32 ticks = SDL_GetTicks(), ticks_elapsed, sim_ticks = 0;
	bool done = false;
	while(!done)
	{
		SDL_Event event;

		while (SDL_PollEvent( &event ) ) 
		{
			switch (event.type )
			{
				case SDL_KEYDOWN:
					switch( event.key.keysym.sym ) 
					{						
						case SDLK_ESCAPE:
							done = true;
							break;
					}
				case SDL_MOUSEMOTION:					
					break;

				case SDL_MOUSEBUTTONDOWN:					
					break;

				case SDL_MOUSEBUTTONUP:					
					break;				

				case SDL_QUIT:
					done = true;
					break;
			}
		}

		// Continuous (key state) keys
		Uint8 *keyState = SDL_GetKeyState( NULL );

		//if (keyState[ SDLK_LEFT])
		
		// Timing
		ticks_elapsed = SDL_GetTicks() - ticks;
		ticks += ticks_elapsed;

		// fixed sim update
		sim_ticks += ticks_elapsed;
		while (sim_ticks > STEPTIME) 
		{
			sim_ticks -= STEPTIME;						

			printf("update sim_ticks %d ticks_elapsed %d\n", sim_ticks, ticks_elapsed );						
			//game->update( (float)STEPTIME / 1000.0f );			
		}	

		// redraw as fast as possible		
		float dtRaw = (float)(ticks_elapsed) / 1000.0f;
				
		//update( dtRaw ); 
		//redraw( g_state );
		

		SDL_GL_SwapBuffers();
	}

	return 1;
}