put_variable(rec_start)
     void *rec_start;
{
    if (netcdf_flag)
      load_netcdf(rec_start);
    if (c_flag)
      gen_load_c(rec_start);
    if (fortran_flag)
      gen_load_fortran(rec_start);
}
