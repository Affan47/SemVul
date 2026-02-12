dlmunmap (void *start, size_t length)
{


  msegmentptr seg = segment_holding (gm, start);
  void *code;

  if (seg && (code = add_segment_exec_offset (start, seg)) != start)
    {
      int ret = munmap (code, length);
      if (ret)
	return ret;
    }

  return munmap (start, length);
}
