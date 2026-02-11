stk_init( int flags )
{

#ifndef WITH_SOUND
    if ( flags & SDL_INIT_AUDIO )
        flags = flags & ~SDL_INIT_AUDIO;
#endif

    if ( SDL_Init( flags ) < 0 )
        STK_ABORT( SDL_GetError() );

    SDL_EnableUNICODE( 1 );

    atexit( stk_quit );

    stk_surface_set_path( "." );

    stk_audio_set_path( "." );

    stk_empty_cursor = stk_cursor_create( 16, 16, 8, 8,
                                  "                "
                                  "                "
                                  "                "
                                  "                "
                                  "                "
                                  "                "
                                  "                "
                                  "                "
                                  "                "
                                  "                "
                                  "                "
                                  "                "
                                  "                "
                                  "                "
                                  "                "
                                  "                " );
    stk_standard_cursor = SDL_GetCursor();
}
