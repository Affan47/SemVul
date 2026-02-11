farmoq(field_t *field1, field_t field2)
{
  size_t   i, len;
  int          nwpv     = field1->nwpv;
  const int    grid1    = field1->grid;
  const double missval1 = field1->missval;
  double *array1  = field1->ptr;
  const int    grid2    = field2.grid;
  const int    nmiss2   = field2.nmiss;
  double missval2 = field2.missval;
  double *array2  = field2.ptr;

  if ( nwpv != 2 ) nwpv = 1;

  len = (size_t) (nwpv*gridInqSize(grid1));

  if ( len != (size_t) (nwpv*gridInqSize(grid2)) )
    cdoAbort("Fields have different gridsize (%s)", __func__);

  if ( nmiss2 > 0 )
    {
      for ( i = 0; i < len; i++ )
	if ( !DBL_IS_EQUAL(array2[i], missval2) )
	  array1[i] = array2[i]*array2[i];
	else
	  array1[i] = missval1;

      field1->nmiss = 0;
      for ( i = 0; i < len; i++ )
	if ( DBL_IS_EQUAL(array1[i], missval1) ) field1->nmiss++;
    }
  else
    {
      for ( i = 0; i < len; i++ )
	array1[i] = array2[i]*array2[i];
    }
}
