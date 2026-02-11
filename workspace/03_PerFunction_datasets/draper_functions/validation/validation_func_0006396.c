expect(char c) {
  if (tix_ch != c) {
    fprintf(stderr,"('%c' '%c')\n",tix_ch,c);
    failure("parse error when reading .tix file");
  }
  tix_ch = getc(tixFile);
}
