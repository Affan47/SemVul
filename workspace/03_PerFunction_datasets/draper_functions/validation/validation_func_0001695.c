getConfEntry(
char *name,
tConfEntry conf[]
) {
 int i;

 DENTER(BASIS_LAYER, "getConfEntry");

 for (i = 0; conf[i].name; i++) {
    if (!strcasecmp(conf[i].name,name)) {
       DRETURN(&conf[i]);
    }
 }

 DRETURN(NULL);
}
