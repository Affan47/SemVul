matr_write(Matrix *M, char *filename) {
  FILE *out = fopen(filename, "w");

  if (!out) {
    if (MATR_DEBUG_MODE) {
      fprintf(stderr, "Bad file name in matr_write: %s\n", filename);
    }
    return;
  }

  matr_write_fp(M, out);

  fclose(out);
}
