main(int argc, char **argv)
{
  int r, c, w, i, n;
  int *matrix;
  int *bitmatrix;

  if (argc != 4) usage(NULL);
  if (sscanf(argv[1], "%d", &r) == 0 || r <= 0) usage("Bad r");
  if (sscanf(argv[2], "%d", &c) == 0 || c <= 0) usage("Bad c");
  if (sscanf(argv[3], "%d", &w) == 0 || w <= 0) usage("Bad w");

  matrix = talloc(int, r*c);

  n = 1;
  for (i = 0; i < r*c; i++) {
    matrix[i] = n;
    n = galois_single_multiply(n, 2, w);
  }

  bitmatrix = jerasure_matrix_to_bitmatrix(c, r, w, matrix);
  jerasure_print_bitmatrix(bitmatrix, r*w, c*w, w);
  return 0;
}
