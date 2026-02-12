static void urlParsePart(struct URL *url, const char *buf, int len) {


  char *name           = NULL;
  for (const char *eol; !!(eol = urlMemstr(buf, len, "\r\n")); ) {
    if (buf == eol) {
      buf             += 2;
      len             -= 2;
      if (name) {
        char *value    = len ? urlMakeString(buf, len) : NULL;
        addToHashMap(&url->args, name, value);
        name           = NULL;
      }
      break;
    } else {
      if (!name && !urlMemcasecmp(buf, len, "content-disposition:")) {
        struct HashMap fields;
        initHashMap(&fields, urlDestroyHashMapEntry, NULL);
        urlParseHeaderLine(&fields, buf + 20, eol - buf - 20);
        if (getRefFromHashMap(&fields, "form-data")) {


          name         = (char *)getFromHashMap(&fields, "name");
          if (name && *name) {
            check(name = strdup(name));
          }
        }
        destroyHashMap(&fields);
      }
      len             -= eol - buf + 2;
      buf              = eol + 2;
    }
  }
  free(name);
}
