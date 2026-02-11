combine_pixels_overlay (DATA8* src, int src_w, int src_h, DATA8* dest, int dest_w, int dest_h, int dest_x, int dest_y)
{
  int x, y, s_idx, d_idx;
  int src_tl_x = 0, src_tl_y = 0;
  int src_br_x = src_w, src_br_y = src_h;
  int tmp_screen, tmp_mult;

  _clip(&src_tl_x, &src_tl_y, &src_br_x, &src_br_y, &dest_x, &dest_y, dest_w, dest_h);

  for (y = src_tl_y; y < src_br_y; y++)
    for (x = src_tl_x; x < src_br_x; x++)
      {
	d_idx = LINEAR((dest_x + x - src_tl_x), (dest_y + y - src_tl_y), dest_w);
	s_idx = LINEAR(x, y, src_w);

	tmp_screen = 255 - (((255 - RD) * (255 - RS)) >> 8);
	tmp_mult   = (RD * RS) >> 8;
	RD = (RD * tmp_screen + (255 - RD) * tmp_mult) >> 8;

	tmp_screen = 255 - (((255 - GD) * (255 - GS)) >> 8);
	tmp_mult   = (GD * GS) >> 8;
	GD = (GD * tmp_screen + (255 - GD) * tmp_mult) >> 8;

	tmp_screen = 255 - (((255 - BD) * (255 - BS)) >> 8);
	tmp_mult   = (BD * BS) >> 8;
	BD = (BD * tmp_screen + (255 - BD) * tmp_mult) >> 8;


      }
}
