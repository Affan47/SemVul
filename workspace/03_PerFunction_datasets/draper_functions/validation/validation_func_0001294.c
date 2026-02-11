operator>>=(cdrStream& s) const
{
  OMNIORB_ASSERT(pd_idl_digits);
  OMNIORB_ASSERT(pd_digits <= pd_idl_digits);
  OMNIORB_ASSERT(pd_scale  <= pd_idl_scale);

  CORBA::Octet buffer[16];

  int digits_to_write = pd_idl_digits;


  if ((digits_to_write % 2) == 0) ++digits_to_write;

  int unscale_to_write = digits_to_write - pd_idl_scale;
  int unscale          = pd_digits       - pd_scale;

  int bi, vi;


  for (bi=0; bi < unscale_to_write - unscale; bi+=2) {
    buffer[bi/2] = 0;
  }
  bi = unscale_to_write - unscale;
  vi = pd_digits - 1;


  for (; vi >= 0; --vi, ++bi) {
    if (bi % 2)
      buffer[bi/2] |= pd_val[vi];
    else
      buffer[bi/2]  = pd_val[vi] << 4;
  }


  if (bi % 2) ++bi;

  for (; bi < digits_to_write; bi+=2) {
    buffer[bi/2] = 0;
  }


  buffer[digits_to_write / 2] |= pd_negative ? 0xD : 0xC;


  s.put_octet_array(buffer, digits_to_write / 2 + 1);
}
