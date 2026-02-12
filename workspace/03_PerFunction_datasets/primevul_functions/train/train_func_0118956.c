extern int main(int argc ARG_UNUSED, char* argv[] ARG_UNUSED)
{
  int r;
  int i;
  FILE* fp = stdout;

  setlocale(LC_ALL, "C");


  for (i = 0; i < (int )(sizeof(Info)/sizeof(ENC_INFO)); i++) {
    r = exec(fp, &Info[i]);
    if (r < 0) {
      fprintf(stderr, "FAIL exec(): %d\n", r);
      return -1;
    }
  }

  return 0;
}
