coerce1D (SV* arg, LONGLONG n)
{
  AV* array;
  I32 i;

  if (is_scalar_ref(arg))
    return (AV*)NULL;

  if (SvTYPE(arg)==SVt_PVGV)
    array = GvAVn((GV*)arg);
  else if (SvROK(arg) && SvTYPE(SvRV(arg))==SVt_PVAV)
    array = (AV *) SvRV(arg);
  else {
    array = (AV*)sv_2mortal((SV*)newAV());
    sv_setsv(arg, sv_2mortal(newRV((SV*) array)));
  }

  for (i=av_len(array)+1; i<n; i++)
    av_store( array, i, newSViv((IV) 0));

  return array;
}
