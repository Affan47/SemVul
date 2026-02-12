bind_keyseq_to_unix_command (line)
     char *line;
{
  Keymap kmap, cmd_xmap;
  char *kseq, *value;
  int i, kstart;

  kmap = rl_get_keymap ();


  i = isolate_sequence (line, 0, 1, &kstart);
  if (i < 0)
    return -1;


  kseq = substring (line, kstart, i);

  for ( ; line[i] && line[i] != ':'; i++)
    ;
  if (line[i] != ':')
    {
      builtin_error (_("%s: missing colon separator"), line);
      FREE (kseq);
      return -1;
    }

  i = isolate_sequence (line, i + 1, 0, &kstart);
  if (i < 0)
    {
      FREE (kseq);
      return -1;
    }


  value = substring (line, kstart, i);


  cmd_xmap = get_cmd_xmap_from_keymap (kmap);
  rl_generic_bind (ISMACR, kseq, value, cmd_xmap);


  rl_bind_keyseq_in_map (kseq, bash_execute_unix_command, kmap);

  free (kseq);
  return 0;
}
