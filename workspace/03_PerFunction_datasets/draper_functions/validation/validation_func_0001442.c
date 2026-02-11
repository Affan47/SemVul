histsort(const char *str, int len) {
  int *arr = malloc((len+1) * sizeof(int));
  int i;
  int *aux = malloc((len+1) * sizeof(int));
  arr[0] = len;

  for (i = 1; i <= len; ++i)
    arr[i] = i-1;
  saux = aux;
  if (len < 10000000) {
    histhelper(str, len, arr, aux, 0, len+1, 0);
  }
  else {
    histzero(str, len, arr, aux, 1, len+1);
  }

  free(aux);
  return arr;

}
