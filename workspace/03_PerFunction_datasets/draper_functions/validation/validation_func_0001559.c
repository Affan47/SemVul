main (int argc, char **argv)
{
  size_t i;
  static struct fileloc pos = { this_file, 0 };


  progname = "gengtype";

  if (argc != 3)
    fatal ("usage: gengtype srcdir input-list");

  srcdir = argv[1];
  srcdir_len = strlen (srcdir);

  read_input_list (argv[2]);
  if (hit_error)
    return 1;

  scalar_char.u.scalar_is_char = true;
  scalar_nonchar.u.scalar_is_char = false;
  gen_rtx_next ();


  pos.line = __LINE__ + 1;
  do_scalar_typedef ("CUMULATIVE_ARGS", &pos); pos.line++;
  do_scalar_typedef ("REAL_VALUE_TYPE", &pos); pos.line++;
  do_scalar_typedef ("FIXED_VALUE_TYPE", &pos); pos.line++;
  do_scalar_typedef ("double_int", &pos); pos.line++;
  do_scalar_typedef ("uint8", &pos); pos.line++;
  do_scalar_typedef ("jword", &pos); pos.line++;
  do_scalar_typedef ("JCF_u2", &pos); pos.line++;
  do_scalar_typedef ("void", &pos); pos.line++;
  do_typedef ("PTR", create_pointer (resolve_typedef ("void", &pos)), &pos);

  for (i = 0; i < num_gt_files; i++)
    parse_file (gt_files[i]);

  if (hit_error)
    return 1;

  set_gc_used (variables);

  open_base_files ();
  write_enum_defn (structures, param_structs);
  write_types (structures, param_structs, &ggc_wtd);
  write_types (structures, param_structs, &pch_wtd);
  write_local (structures, param_structs);
  write_roots (variables);
  write_rtx_next ();
  close_output_files ();

  if (hit_error)
    return 1;
  return 0;
}
