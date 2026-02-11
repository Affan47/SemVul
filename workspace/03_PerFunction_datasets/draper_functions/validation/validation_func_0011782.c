z_test_attr( zword_t obj, zword_t bit )
{
   zword_t objp;
   zbyte_t value;

   assert( O3_ATTRIBUTES == O4_ATTRIBUTES );

#ifdef STRICTZ
   if ( obj == 0 )
   {
      report_strictz_error( STRZERR_TEST_ATTR, "@test_attr called with object 0" );
      conditional_jump( FALSE );
      return;
   }
#endif


   objp = get_object_address( obj ) + ( bit >> 3 );


   value = get_byte( objp );


   conditional_jump( ( value >> ( 7 - ( bit & 7 ) ) ) & 1 );

}
