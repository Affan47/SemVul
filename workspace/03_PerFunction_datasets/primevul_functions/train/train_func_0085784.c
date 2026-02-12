static char Lookahead(unsigned char *word, int how_far) {
  char letter_ahead = '\0';
  int idx;
  for (idx = 0; word[idx] != '\0' && idx < how_far; idx++);


  letter_ahead = (char)word[idx];


  return letter_ahead;
}
