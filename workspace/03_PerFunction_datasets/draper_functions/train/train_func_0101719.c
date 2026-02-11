combine_pixels_normal (DATA8* src, int src_w, int src_h, DATA8* dest, int dest_w, int dest_h, int dest_x, int dest_y)
{
  int x, y, s_idx, d_idx;
  int src_tl_x = 0, src_tl_y = 0;
  int src_br_x = src_w, src_br_y = src_h;

  int b;
  unsigned char src_alpha;
  unsigned char new_alpha;
  float ratio, compl_ratio;
  long tmp;

  _clip(&src_tl_x, &src_tl_y, &src_br_x, &src_br_y, &dest_x, &dest_y, dest_w, dest_h);

  for (y = src_tl_y; y < src_br_y; y++)
    for (x = src_tl_x; x < src_br_x; x++)
      {
	d_idx = LINEAR((dest_x + x - src_tl_x), (dest_y + y - src_tl_y), dest_w);
	s_idx = LINEAR(x, y, src_w);

	src_alpha = AS;

	if (src_alpha != 0)
	  {
	    if (src_alpha == 255)
	      new_alpha = src_alpha;
	    else
	      new_alpha = AD + INT_MULT((255 - AD), src_alpha, tmp);

	    b = 3;
	    if (new_alpha != 0)
	      {
		ratio = (float) src_alpha / new_alpha;
		compl_ratio = 1.0 - ratio;

		do
		  {
		    b--;
		    dest[d_idx + b] =
		      (unsigned char) (src[s_idx + b] * ratio + dest[d_idx + b] * compl_ratio + EPS);
		  }
		while (b);
	      }

	    AD = new_alpha;
	  }
      }
}
