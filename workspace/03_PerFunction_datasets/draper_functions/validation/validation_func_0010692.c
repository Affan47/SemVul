unpack3D(SV* arg, void* var, LONGLONG* dims, int datatype, int perlyunpack)
{
  long i,j,skip;
  AV *array1,*array2;
  SV *tmp_sv;
  char *tmp_var = (char *)var;

  if (! PERLYUNPACKING(perlyunpack) && datatype != TSTRING) {
    unpack2scalar(arg,var,dims[0]*dims[1]*dims[2],datatype);
    return;
  }

  coerce1D(arg,dims[0]);
  array1 = (AV*)SvRV(arg);

  skip = dims[2] * sizeof_datatype(datatype);
  for (i=0; i<dims[0]; i++) {
    tmp_sv = *av_fetch(array1,i,0);
    coerce1D(tmp_sv,dims[1]);
    array2 = (AV*)SvRV(tmp_sv);
    for (j=0; j<dims[1]; j++) {
      unpack1D(*av_fetch(array2,j,0),tmp_var,dims[2],datatype,perlyunpack);
      tmp_var += skip;
    }
  }
}
