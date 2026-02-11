draw_lemming (a_pixel *dest, const a_lemming *lem, unsigned int pos)
{
  const a_pixel *src;

  assert (lem >= lemmings_support
	  && lem < lemmings_support + lemmings_total);

  if (pos == lem->pos_tail) {
    int c = lem->couleur;
    a_dir d = lem->dir;
    src = vehicles_img.buffer + 164 * 320;
    src += 64 * c;
    if (d & 1)
      src += 8 * 320;


    if (pos != lem->pos_head) {
      src += lemmings_anim_offset;
      if (d == w_up)
	dest -= (lemmings_move_offset / 6553) * xbuf;
      if (d == w_right)
	dest += lemmings_move_offset / 5461;
      if (d == w_down)
	dest += (lemmings_move_offset / 6553) * xbuf;
      if (d == w_left)
	dest -= lemmings_move_offset / 5461;
    }
    copy_lemming_transp (src, dest);
  } else {
    assert (pos == lem->pos_head);
  }
}
