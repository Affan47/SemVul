simple_c_interface_read_char(uint16_t UNUSED(tenth_seconds),
    uint32_t UNUSED(verification_routine), int *UNUSED(tenth_seconds_elapsed))
{
  int result;
#ifdef ENABLE_READCHAR_VIA_TERMIOS
  struct termios org_opts, new_opts;
#endif

  if (line_length != -1)
    wordwrap_flush_output(output_wordwrapper);

#ifdef ENABLE_READCHAR_VIA_TERMIOS

  tcgetattr(STDIN_FILENO, &org_opts);
  memcpy(&new_opts, &org_opts, sizeof(new_opts));
  new_opts.c_lflag
    &= ~(ICANON | ECHO | ECHOE | ECHOK | ECHONL | ECHOKE | ICRNL);
  tcsetattr(STDIN_FILENO, TCSANOW, &new_opts);
  result = getchar();
  result = unicode_char_to_zscii_input_char(result & 0xff);
  if (result == 0xff)
    result = -1;
  tcsetattr(STDIN_FILENO, TCSANOW, &org_opts);

  return result;

#else

  zscii input_zscii;
  int input;

  if ((input = fgetc(stdin)) == EOF)
    exit(-1);

  result = -1;

  while ((input != 10) && (input != 13))
  {
    if (result == -1)
    {
      if ((input_zscii=unicode_char_to_zscii_input_char(input & 0xff)) != 0xff)
        result = input_zscii;
    }

    if ((input = fgetc(stdin)) == EOF)
      exit(-1);
  }

  if (result == -1)
    result = 10;

#endif

  return result;
}
