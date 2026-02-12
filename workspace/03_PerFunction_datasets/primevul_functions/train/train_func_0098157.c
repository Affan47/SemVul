static int vcmp(struct mg_str s1, const char *s2) {


  return mg_vcmp(&s1, s2) == 0;
}
