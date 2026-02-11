dump_gimple_stmt (int dump_kind, int extra_dump_flags, gimple gs, int spc)
{
  if (dump_file && (dump_kind & pflags))
    print_gimple_stmt (dump_file, gs, spc, dump_flags | extra_dump_flags);

  if (alt_dump_file && (dump_kind & alt_flags))
    print_gimple_stmt (alt_dump_file, gs, spc, dump_flags | extra_dump_flags);
}
