shuffle (int arr[], int len) {
  int t, i, j, s;
  for(t=0; t<len; ++t){
    i = rand() % len;
    j = rand() % len;
    s = arr[i];
    arr[i] = arr[j];
    arr[j] = s;
  }
}
