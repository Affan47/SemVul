df_insn_modify (struct df *df, basic_block bb, rtx insn)
{
  unsigned int uid;

  uid = INSN_UID (insn);
  if (uid >= df->insn_size)
    df_insn_table_realloc (df, uid);

  bitmap_set_bit (df->bbs_modified, bb->index);
  bitmap_set_bit (df->insns_modified, uid);


}
