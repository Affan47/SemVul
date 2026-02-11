ft_ansi_stream_io( FT_Stream       stream,
                     unsigned long   offset,
                     unsigned char*  buffer,
                     unsigned long   count )
  {
    FT_FILE*  file;


    if ( !count && offset > stream->size )
      return 1;

    file = STREAM_FILE( stream );

    if ( stream->pos != offset )
      ft_fseek( file, (long)offset, SEEK_SET );

    return (unsigned long)ft_fread( buffer, 1, count, file );
  }
