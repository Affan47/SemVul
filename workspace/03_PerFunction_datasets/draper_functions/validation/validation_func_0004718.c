NESPSG_sh_update(void)
{
  int i;

  if (real_rate==0) return;

  for (i = 0;i < chip_max;i++)
  {
    apu_update(i);
#ifndef USE_QUEUE
    APU[i].buf_pos=0;
#endif
    mixer_play_streamed_sample_16(channel+i,APU[i].buffer,buffer_size,real_rate);
  }
}
