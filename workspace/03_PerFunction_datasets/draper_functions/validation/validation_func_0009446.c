z_log_shift( zword_t a, zword_t b )
{

   if ( ( ZINT16 ) b > 0 )
      store_operand( (zword_t)( a << ( ZINT16 ) b ) );
   else
      store_operand( (zword_t)( a >> -( ( ZINT16 ) b ) ) );

}
