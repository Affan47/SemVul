multiply(char *m) {
 char *c;
    c = strchr(m, 's'); if(c) { return 1; }
    c = strchr(m, 'm'); if(c) { return 60; }
    c = strchr(m, 'h'); if(c) { return 3600; }
    c = strchr(m, 'd'); if(c) { return 86400; }

 return 1;
}
