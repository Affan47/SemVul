send_next_char(int trig_signal)
{
  char c;

  c = s[str_index];

  c = toupper(c);


  tab_index = 0;
  while (cw_chars[tab_index].key != 0) {
    if (cw_chars[tab_index].key == c) {


      D(putchar(c);
	putchar(':');
	putchar(' ');
	fflush(stdout));

      cw_char_len = strlen(cw_chars[tab_index].cw);
      cw_char_index = 0;
      send_next_element(SIGALRM);
      return;
    } else {
      tab_index++;
    }
  }

  fprintf(stderr, "send_next_char: char not recognized\n");
}
