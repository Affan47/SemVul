get_current_reader (void)
{
  struct vreader_s *vr;


  vr = &vreader_table[0];


  if (!vr->valid)
    {
      vr->slot = -1;
      vr->valid = 1;
    }


  if (vr->slot == -1)
    {
      vr->slot = apdu_open_reader (opt.reader_port);


      if (vr->slot == -1)
	{
	  vr->valid = 0;
	}
    }


  return vr->valid ? 0 : -1;
}
