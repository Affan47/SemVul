check() throw ( exception ) {
  const unsigned int a_size( 23 );
  char a[a_size];
  char type_a[4];
  char length_a[4];
  int  length;
  bool found_IDAT = false;

  if ( ! in->read( a, a_size ) )       return false;
  if ( ! equals( a, 0, MAGIC, 0, 5 ) ) return false;

  width  = getIntBigEndian( a, 13 );
  height = getIntBigEndian( a, 17 );
  if ( width < 1 || height < 1 ) return false;

  bitsPerPixel  = a[21] & 0xff;
  int colorType = a[22] & 0xff;
  if ( colorType == 2 || colorType == 6 ) bitsPerPixel *= 3;

  format = FORMAT_PNG;

  length = 3;


  while( true ) {
    in->skip( length + 4 );
    if ( ! in->read( length_a, 4 ) ) return false;
    if ( ! in->read( type_a,   4 ) ) return false;

    if ( equals( type_a, 0, IEND, 0, 4 ) ) {

      break;
    }

    length = getIntBigEndian( length_a, 0 );
    if ( length == 0 ) continue;

    if ( ! found_IDAT && equals( type_a, 0, pHYs, 0, 4 ) ) {

      if ( ! in->read( a, 9 ) ) return false;

      if ( a[8] == 0x01 ) {

        int ppi = (int)(getIntBigEndian( a, 0 ) * 0.0254);
        physicalWidthDpi = static_cast<int>( ppi );
        if ( ppi - physicalWidthDpi >= 0.5) physicalWidthDpi++;


        ppi = (int)(getIntBigEndian( a, 4 ) * 0.0254);
        physicalHeightDpi = static_cast<int>( ppi );
        if ( ppi - physicalHeightDpi >= 0.5) physicalHeightDpi++;
      }
      if ( ! collectComments ) break;
	  length -= 9;

    } else if ( equals( type_a, 0, IDAT, 0, 4 ) ) {

      found_IDAT = true;
      if ( ! collectComments ) break;

    }

    length -= handleComments( length, type_a );

  }
  return true;
}
