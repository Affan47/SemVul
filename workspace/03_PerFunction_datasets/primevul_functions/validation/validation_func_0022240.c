invalid_command()
{
    int save_token = c_token;
#ifdef OS2
    if (token[c_token].is_token) {
      int rc;
      rc = ExecuteMacro(gp_input_line + token[c_token].start_index,
	      token[c_token].length);
      if (rc == 0) {
	 c_token = num_tokens = 0;
	 return;
      }
    }
#endif


    while (!END_OF_COMMAND)
	c_token++;
    int_error(save_token, "invalid command");
}
