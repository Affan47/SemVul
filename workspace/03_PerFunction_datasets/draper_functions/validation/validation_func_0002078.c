close_sbuf( void )
  {
  clear_yank_buffer();
  clear_undo_stack();
  if( sfp )
    {
    if( fclose( sfp ) != 0 )
      {
      show_strerror( 0, errno );
      set_error_msg( "Cannot close temp file" );
      return false;
      }
    sfp = 0;
    }
  sfpos = 0;
  seek_write = false;
  return true;
  }
