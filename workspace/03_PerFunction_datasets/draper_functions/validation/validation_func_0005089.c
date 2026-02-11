df_modified_p (struct df *df, bitmap blocks)
{
  int update = 0;
  basic_block bb;

  if (!df->n_bbs)
    return 0;

  FOR_EACH_BB (bb)
    if (bitmap_bit_p (df->bbs_modified, bb->index)
	&& (! blocks || (blocks == (bitmap) -1) || bitmap_bit_p (blocks, bb->index)))
    {
      update = 1;
      break;
    }

  return update;
}
