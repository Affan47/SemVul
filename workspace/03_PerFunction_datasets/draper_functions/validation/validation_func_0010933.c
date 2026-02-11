debugCheckCo (INFO *info) {
  unsigned int j = 0;
  unsigned int cos_count = 0;
  unsigned int curr_j;


  for (unsigned int i = 0; i < info -> m; i++) {
    cos_count = GET_COS_POSITION (i, 0);
    curr_j = 0;
    for (unsigned int pos_j = 1; pos_j <= cos_count; pos_j++) {
      j = GET_COS_POSITION (i, pos_j);
      while (curr_j < j) {
        fprintf (stderr, "X");
        curr_j++;
      }
      fprintf (stderr, "O");
    }

    while (curr_j < info -> n) {
      fprintf (stderr, "X");
      curr_j++;
    }

    fprintf (stderr, "\n");
  }

  fprintf (stderr, "-----\n");

  return;
}
