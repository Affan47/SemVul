writeAlphaPGMFile(char *fileName) {
  FILE *f;

  if (!alpha) {
    return splashErrModeMismatch;
  }
  if (!(f = fopen(fileName, "wb"))) {
    return splashErrOpenFile;
  }
  fprintf(f, "P5\n%d %d\n255\n", width, height);
  fwrite(alpha, 1, width * height, f);
  fclose(f);
  return splashOk;
}
