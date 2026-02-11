emit_mode_base_align (void)
{
  int c;
  struct mode_data *m;

  print_maybe_const_decl ("%sunsigned char",
			  "mode_base_align", "NUM_MACHINE_MODES",
			  alignment);

  for_all_modes (c, m)
    tagged_printf ("%u", m->alignment, m->name);

  print_closer ();
}
