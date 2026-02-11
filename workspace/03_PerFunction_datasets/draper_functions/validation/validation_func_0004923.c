fec_rb_destroy(void) {
  if (fec_rb != NULL) {
    while (fec_rb_cnt)
      fec_rb_pop();

    free(fec_rb);
    fec_rb = NULL;
  }

  fec_rb_size = 0;
  fec_rb_clear();
}
