echo_area_initialize_node (void)
{
  register int i;

  for (i = input_line_end; (unsigned int) i < sizeof (input_line); i++)
    input_line[i] = ' ';

  input_line[i - 1] = '\n';
  window_set_node_of_window (the_echo_area, &input_line_node);
  input_line[input_line_end] = '\n';
}
