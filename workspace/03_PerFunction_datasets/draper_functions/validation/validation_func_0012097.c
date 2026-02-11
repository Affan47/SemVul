zone_from_range(char *range)
{
   int start = 0;
   int end   = 0;
   int bits  = 0;

   if ( set_range(range, &start, &end, &bits) == 1 )
   {
      return build_reverse_ip(range, -bits, start, end);
   }
   return NULL;
}
