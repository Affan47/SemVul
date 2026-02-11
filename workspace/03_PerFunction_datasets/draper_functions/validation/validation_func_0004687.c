load_lut (unsigned char * lut,
  int in_bits, int out_bits,
  int out_min, int out_max,
  int slope, int offset)
{
  SANE_Status ret = SANE_STATUS_GOOD;
  int i, j;
  double shift, rise;
  int max_in_val = (1 << in_bits) - 1;
  int max_out_val = (1 << out_bits) - 1;
  unsigned char * lut_p = lut;

  DBG (10, "load_lut: start\n");


  rise = tan((double)slope/127 * M_PI/2) * max_out_val / max_in_val;


  shift = (double)max_out_val/2 - (rise*max_in_val/2);


  shift += (double)offset / 127 * max_out_val / 2;

  for(i=0;i<=max_in_val;i++){
    j = rise*i + shift;

    if(j<out_min){
      j=out_min;
    }
    else if(j>out_max){
      j=out_max;
    }

    *lut_p=j;
    lut_p++;
  }

  hexdump(5, "load_lut: ", lut, max_in_val+1);

  DBG (10, "load_lut: finish\n");
  return ret;
}
