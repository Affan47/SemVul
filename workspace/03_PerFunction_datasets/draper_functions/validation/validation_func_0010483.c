TestDataPath( char const * path )
{
    if ( TestPath( path, "language/english_base.txt") )
    {
#ifdef DEBUG_PATH
        con << "Data path " << path << " is good.\n";
#endif

        ReplacePath( st_DataDir, path );

        return true;
    }

#ifdef DEBUG_PATH
    con << "Data path " << path << " is bad!\n";
#endif

    return false;
}
