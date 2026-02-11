copyRLEpixels(rgba *dest,unsigned npixels,uint32_t ptr,convertParams *params)
{
  unsigned i,j ;
  rgba base_pixel = params->base_pixel ;

#ifdef xDEBUG
  fprintf(stderr,"RLE stream at %x, want %u x %u pixels, base %x\n",
          ptr,params->bpp,npixels,base_pixel);
#endif


  if( params->shift[0] < -1 )
    base_pixel = 0 ;
  for( j = npixels ; j-- ; )
    dest[j] = base_pixel ;

  for( i = 0 ; i < params->bpp ; i++ ) {
    int shift = params->shift[i] ;
    if( shift < 0 )
      shift = 0 ;
    for( j = 0 ; j < npixels ; ) {
      int countspec ;
      unsigned count ;
      xcfCheckspace(ptr,2,"RLE data stream");
      countspec = (int8_t) xcf_file[ptr++] ;
      count = countspec >= 0 ? countspec+1 : -countspec ;
      if( count == 128 ) {
        xcfCheckspace(ptr,3,"RLE long count");
        count = xcf_file[ptr++] << 8 ;
        count += xcf_file[ptr++] ;
      }
      if( j + count > npixels )
        FatalBadXCF("Overlong RLE run at %"PRIX32" (plane %u, %u left)",
                    ptr,i,npixels-j);
      if( countspec >= 0 ) {
        rgba data = (uint32_t) xcf_file[ptr++] << shift ;
        while( count-- )
          dest[j++] += data ;
      } else {
        while( count-- )
          dest[j++] += (uint32_t) xcf_file[ptr++] << shift ;
      }
    }
    if( i == 0 && params->shift[0] < 0 ) {
      const rgba *lookup = params->lookup ;
      base_pixel = params->base_pixel ;
      for( j = npixels ; j-- ; ) {
        dest[j] = lookup[dest[j]-base_pixel] + base_pixel ;
      }
    }
  }
#ifdef xDEBUG
  fprintf(stderr,"RLE decoding OK at %"PRIX32"\n",ptr);


#endif
}
