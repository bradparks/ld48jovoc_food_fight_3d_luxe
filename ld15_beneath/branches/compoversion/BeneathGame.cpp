#include <tweakval.h>
#include <gamefontgl.h>

#include <BeneathGame.h>

BeneathGame::BeneathGame() :
	m_isInit( false )
{
}

// fixed update, for gameplay stuff
void BeneathGame::updateSim( float dt )
{
	vec2f playerDir( 0.0f, 0.0f );

	printf("UpdateSim %3.2f\n", dt );
	// Continuous (key state) keys
	Uint8 *keyState = SDL_GetKeyState( NULL );
	if ((keyState[SDLK_LEFT]) && (!keyState[SDLK_RIGHT]))
	{
		playerDir.x = -1.0;
	}
	else if ((!keyState[SDLK_LEFT]) && (keyState[SDLK_RIGHT]))
	{
		playerDir.x = 1.0;
	}
	if ((keyState[SDLK_UP]) && (!keyState[SDLK_DOWN]))
	{
		playerDir.y = 1.0;
	}
	else if ((!keyState[SDLK_UP]) && (keyState[SDLK_DOWN]))
	{
		playerDir.y = -1.0;
	}

	// update player
	m_player->pos += playerDir * _TV( 100.0f ) * dt;
}

// "as fast as possible" update for effects and stuff
void BeneathGame::update( float dt )
{
	printf("Update %3.2f\n", dt );
}

void BeneathGame::init()
{
	// Load the font image
	ILuint ilFontId;
	ilGenImages( 1, &ilFontId );
	ilBindImage( ilFontId );		
	
	if (!ilLoadImage( (ILstring)"gamedata/andelemo.png" )) {
		printf("Loading font image failed\n");
	}
	
	// Make a GL texture for it
	m_glFontTexId = ilutGLBindTexImage();
	m_fntFontId = gfCreateFont( m_glFontTexId );

	// A .finfo file contains the metrics for a font. These
	// are generated by the Fontpack utility.
	gfLoadFontMetrics( m_fntFontId, "gamedata/andelemo.finfo");

	printf("font has %d chars\n", 
		gfGetFontMetric( m_fntFontId, GF_FONT_NUMCHARS ) );					

	// Now load game shapes
	m_player = Shape::simpleShape( "gamedata/player.png" );
	m_player->pos = vec2f( 300, 200 );
}
	
void BeneathGame::redraw()
{
	glClearColor( _TV( 0.1f ), _TV(0.2f), _TV( 0.4f ), 1.0 );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	if (!m_isInit)
	{
		m_isInit = true;
		init();
	}
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();

	gluOrtho2D( 0, 800, 0, 600 ) ;

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	// Draw player shape
	glEnable( GL_TEXTURE_2D );
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );		

	glBindTexture( GL_TEXTURE_2D, m_player->m_texId );	

	glColor3f( 1.0, 1.0, 1.0 );
	glBegin( GL_QUADS );
	glTexCoord2d( m_player->st0.x, m_player->st1.y ); 
	glVertex3f( m_player->pos.x, m_player->pos.y, 0.0 );

	glTexCoord2d( m_player->st0.x, m_player->st0.y  ); 
	glVertex3f( m_player->pos.x, m_player->pos.y + 32, 0.0 );
	
	glTexCoord2d( m_player->st1.x, m_player->st0.y );
	glVertex3f( m_player->pos.x+32, m_player->pos.y + 32, 0.0 );

	glTexCoord2d( m_player->st1.x, m_player->st1.y  ); 
	glVertex3f( m_player->pos.x+32, m_player->pos.y, 0.0 );
	glEnd();

	// Title text
	gfEnableFont( m_fntFontId, 32 );	
	gfBeginText();
	glTranslated( _TV(260), _TV(500), 0 );
	gfDrawString( "The World Beneath" );
	gfEndText();

	// Bottom text
	gfEnableFont( m_fntFontId, 20 );	
	gfBeginText();
	glTranslated( _TV(180), _TV(10), 0 );
	gfDrawString( "LudumDare 15 - Joel Davis (joeld42@yahoo.com)" );
	gfEndText();
}