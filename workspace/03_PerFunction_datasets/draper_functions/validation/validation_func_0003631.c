xdr_table_obj (XDR *xdrs, table_obj *objp)
{
  bool_t res = xdr_string (xdrs, &objp->ta_type, 64);
  if (__builtin_expect (res, TRUE))
    {
      res = xdr_int (xdrs, &objp->ta_maxcol);
      if (__builtin_expect (res, TRUE))
	{
	  res = xdr_u_char (xdrs, &objp->ta_sep);
	  if (__builtin_expect (res, TRUE))
	    {
	      res = xdr_array (xdrs, (void *) &objp->ta_cols.ta_cols_val,
			       &objp->ta_cols.ta_cols_len, ~0,
			       sizeof (table_col), (xdrproc_t) xdr_table_col);
	      if (__builtin_expect (res, TRUE))
		res = xdr_string (xdrs, &objp->ta_path, ~0);
	    }
	}
    }
  return res;
}
