df_md_top_dump (basic_block bb, FILE *file)
{
  struct df_md_bb_info *bb_info = df_md_get_bb_info (bb->index);
  if (!bb_info)
    return;

  fprintf (file, ";; md  in  \t");
  df_print_regset (file, &bb_info->in);
  fprintf (file, ";; md  init  \t");
  df_print_regset (file, &bb_info->init);
  fprintf (file, ";; md  gen \t");
  df_print_regset (file, &bb_info->gen);
  fprintf (file, ";; md  kill \t");
  df_print_regset (file, &bb_info->kill);
}
