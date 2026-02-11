bg_xing_update(bg_xing_t * xing, int bytes)
  {
  if(xing->frame_positions_alloc < xing->num_frames + 1)
    {
    xing->frame_positions_alloc += 1024;
    xing->frame_positions = realloc(xing->frame_positions,
                                    xing->frame_positions_alloc *
                                    sizeof(*xing->frame_positions));
    }
  xing->frame_positions[xing->num_frames] = xing->total_bytes;
  xing->num_frames++;
  xing->total_bytes+= bytes;
  }
