xdr_endpoint (XDR *xdrs, endpoint *objp)
{
  bool_t res =  xdr_string (xdrs, &objp->uaddr, ~0);
  if (__builtin_expect (res, TRUE))
    {
      res = xdr_string (xdrs, &objp->family, ~0);
      if (__builtin_expect (res, 1))
	res = xdr_string (xdrs, &objp->proto, ~0);
    }
  return res;
}
