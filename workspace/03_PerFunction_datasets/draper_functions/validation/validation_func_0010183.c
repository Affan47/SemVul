FT_Stream_Open( FT_Stream    stream,
                  const char*  filepathname )
  {
    FT_FILE*  file;


    if ( !stream )
      return FT_THROW( Invalid_Stream_Handle );

    stream->descriptor.pointer = NULL;
    stream->pathname.pointer   = (char*)filepathname;
    stream->base               = NULL;
    stream->pos                = 0;
    stream->read               = NULL;
    stream->close              = NULL;

    file = ft_fopen( filepathname, "rb" );
    if ( !file )
    {
      FT_ERROR(( "FT_Stream_Open:"
                 " could not open `%s'\n", filepathname ));

      return FT_THROW( Cannot_Open_Resource );
    }

    ft_fseek( file, 0, SEEK_END );
    stream->size = (unsigned long)ft_ftell( file );
    if ( !stream->size )
    {
      FT_ERROR(( "FT_Stream_Open:" ));
      FT_ERROR(( " opened `%s' but zero-sized\n", filepathname ));
      ft_fclose( file );
      return FT_THROW( Cannot_Open_Stream );
    }
    ft_fseek( file, 0, SEEK_SET );

    stream->descriptor.pointer = file;
    stream->read  = ft_ansi_stream_io;
    stream->close = ft_ansi_stream_close;

    FT_TRACE1(( "FT_Stream_Open:" ));
    FT_TRACE1(( " opened `%s' (%d bytes) successfully\n",
                filepathname, stream->size ));

    return FT_Err_Ok;
  }
