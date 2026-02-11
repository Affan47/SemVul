ft_gzip_get_uncompressed_size( FT_Stream  stream )
  {
    FT_Error  error;
    FT_ULong  old_pos;
    FT_ULong  result = 0;


    old_pos = stream->pos;
    if ( !FT_Stream_Seek( stream, stream->size - 4 ) )
    {
      result = FT_Stream_ReadULongLE( stream, &error );
      if ( error )
        result = 0;

      (void)FT_Stream_Seek( stream, old_pos );
    }

    return result;
  }
