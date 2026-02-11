pad(char *string, int length) {
  int l;

  l=strlen(string);
  while(l<length) {
      string[l] = ' ';
      l++;
  }

  string[l]='\0';
  return string;
}
