LoadAll(const tString& filename)
{
    std::ifstream f;

    tTextFileRecorder stream( tDirectories::Config(), filename );
    while( !stream.EndOfFile() )
    {
        tString line( stream.GetLine().c_str() );
        if ( line[0] != '#' )
            LoadSingleAI( line );
    }
}
