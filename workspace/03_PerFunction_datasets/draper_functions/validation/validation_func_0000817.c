vector_from_int(
  vector* vec,
  int     value
) { PROFILE(VECTOR_FROM_INT);

  bool retval = TRUE;

  switch( vec->suppl.part.data_type ) {
    case VDATA_UL :
      {
        ulong        scratchl[UL_DIV(MAX_BIT_WIDTH)];
        ulong        scratchh[UL_DIV(MAX_BIT_WIDTH)];
        unsigned int i;
        unsigned int size        = (vec->width < (sizeof( int ) << 3)) ? UL_SIZE( vec->width ) : UL_SIZE( sizeof( int ) << 3 );
        bool         sign_extend = (value < 0) && (vec->width > (sizeof( int ) << 3));
        unsigned int shift       = (UL_BITS <= (sizeof( int ) << 3)) ? UL_BITS : (sizeof( int ) << 3);
        for( i=0; i<size; i++ ) {
          scratchl[i] = (ulong)value & UL_SET;
          scratchh[i] = 0;

          value >>= shift;

        }
        if( sign_extend ) {
          vector_sign_extend_ulong( scratchl, scratchh, UL_SET, UL_SET, (vec->width - 1), vec->width );
        } else {
          size = UL_SIZE( vec->width );
          for( ; i<size; i++ ) {
            scratchl[i] = scratchh[i] = 0;
          }
        }
        retval = vector_set_coverage_and_assign_ulong( vec, scratchl, scratchh, 0, (vec->width - 1) );
      }
      break;
    case VDATA_R64 :
      retval              = !DEQ( vec->value.r64->val, (double)value );
      vec->value.r64->val = (double)value;
      break;
    case VDATA_R32 :
      retval              = !FEQ( vec->value.r32->val, (float)value );
      vec->value.r32->val = (float)value;
      break;
    default :  assert( 0 );  break;
  }


  vec->suppl.part.is_signed = 1;

  PROFILE_END;

  return( retval );

}
