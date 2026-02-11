debug_prompt(void)
{
  char buffer[513];
  exit_debugger = FALSE;
  perform_displays();
  while(!exit_debugger) {
    if(db_prompt)
      infix_print_string(db_prompt);
    else
      infix_print_string("(nitfol) ");
    infix_get_string(buffer, 512);
    process_debug_command(buffer);
  }
}
