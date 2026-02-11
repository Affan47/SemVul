sprow_idx(const SPROW *r, int col)
#endif
{
   register int		lo, hi, mid;
   int			tmp;
   register row_elt	*r_elt;


   r_elt = r->elt;
   if ( r->len <= 0 )
     return -2;


   lo = 0;		hi = r->len - 1;	mid = lo;
   while ( lo <= hi )
   {
      mid = (hi + lo)/2;
      if ( (tmp=r_elt[mid].col-col) > 0 )
	hi = mid-1;
      else if ( tmp < 0 )
	lo = mid+1;
      else
	return mid;
   }
   tmp = r_elt[mid].col - col;

   if ( tmp > 0 )
     return -(mid+2);
   else
     return -(mid+3);
}
