printer_zxp_write(libspectrum_word port GCC_UNUSED,
                              libspectrum_byte b)
{
if(!settings_current.printer)
  return;
if(plusd_available)
  return;
if(!zxpspeed)
  {
  if(!(b&4))
    {
    zxpspeed=(b&2)?1:2;
    zxpframes=frames;
    zxpcycles=tstates;
    zxpstylus=b&128;
    zxppixel=-1;
    zxplineofchar=0;
    }
  }
else
  {
  int frame=frames-zxpframes;
  int cycles=tstates-zxpcycles;
  int i,x;
  int cpp=440/zxpspeed;

  if(frame>400)
    frame=400;
  cycles+=frame*machine_current->timings.tstates_per_frame;
  x=cycles/cpp-64;
  for(i=zxppixel;i<x && i<256;i++)
    if(i>=0)
      zxpline[i]=zxpstylus;
  if(x>=256 && zxppixel<256)
    printer_zxp_output_line();

  while(x>=320)
    {
    zxpcycles+=cpp*384;
    if(zxpcycles>=machine_current->timings.tstates_per_frame)
      zxpcycles-=machine_current->timings.tstates_per_frame,zxpframes++;
    x-=384;
    if(zxpnewspeed)
      {
      zxpspeed=zxpnewspeed;
      zxpnewspeed=0;
      x=(x+64)*cpp;
      cpp=440/zxpspeed;
      x=x/cpp-64;
      }
    for(i=0;i<x && i<256;i++)
      zxpline[i]=zxpstylus;
    if(x>=256)
      printer_zxp_output_line();
    }
  if(x<0)
    x=-1;
  if(b&4)
    {
    if(x>=0 && x<256)
      {
      for(i=x;i<256;i++)
        zxpline[i]=zxpstylus;
      printer_zxp_output_line();
      }
    zxpspeed=zxpstylus=0;


    zxplineofchar=0;


    printer_zxp_update_header();
    }
  else
    {
    zxppixel=x;
    zxpstylus=b&128;
    if(x<0)
      zxpspeed=(b&2)?1:2;
    else
      {
      zxpnewspeed=(b&2)?1:2;
      if(zxpnewspeed==zxpspeed)
        zxpnewspeed=0;
      }
    }
  }
}
