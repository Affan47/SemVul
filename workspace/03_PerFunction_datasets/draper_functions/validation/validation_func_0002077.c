load( const string &wav)
{
    XTRACE();
    if( !ResourceManagerS::instance()->selectResource( wav))
    {
        LOG_ERROR << "Wav file [" << wav << "] not found." << endl;
        return 0;
    }

    ziStream &infile = ResourceManagerS::instance()->getInputStream();
    SDL_RWops *src = RWops_from_ziStream( infile);

    Mix_Chunk *mix = Mix_LoadWAV_RW(src, 0);
    if( !mix)
    {
        LOG_ERROR << "Failed to load wav: [" << wav << "]" << endl;
        LOG_ERROR << SDL_GetError() << endl;
        return 0;
    }
    SDL_RWclose( src);

    return mix;
}
