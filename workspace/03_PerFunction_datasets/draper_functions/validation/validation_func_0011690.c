rl_initialize_funmap ()
{
  register int i;

  if (funmap_initialized)
    return;

  for (i = 0; default_funmap[i].name; i++)
    rl_add_funmap_entry (default_funmap[i].name, default_funmap[i].function);

  funmap_initialized = 1;
  funmap_program_specific_entry_start = i;
}
