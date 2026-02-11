findFilterByFileName( const QString & fileName )
{
    if ( fileName.endsWith( QLatin1String(".gz"), Qt::CaseInsensitive ) )
    {
        return new KGzipFilter;
    }
#if HAVE_BZIP2_SUPPORT
    if ( fileName.endsWith( QLatin1String(".bz2"), Qt::CaseInsensitive ) )
    {
        return new KBzip2Filter;
    }
#endif
#if HAVE_XZ_SUPPORT
    if ( fileName.endsWith( QLatin1String(".lzma"), Qt::CaseInsensitive ) || fileName.endsWith( QLatin1String(".xz"), Qt::CaseInsensitive ) )
    {
        return new KXzFilter;
    }
#endif
    else
    {


    }

    return 0;
}
