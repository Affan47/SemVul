static char *concat_url(const char *base, const char *relurl)
{


  char *newest;
  char *protsep;
  char *pathsep;
  size_t newlen;
  bool host_changed = FALSE;

  const char *useurl = relurl;
  size_t urllen;


  char *url_clone = strdup(base);

  if(!url_clone)
    return NULL;


  protsep = strstr(url_clone, "//");
  if(!protsep)
    protsep = url_clone;
  else
    protsep += 2;

  if('/' != relurl[0]) {
    int level = 0;


    pathsep = strchr(protsep, '?');
    if(pathsep)
      *pathsep = 0;


    if(useurl[0] != '?') {
      pathsep = strrchr(protsep, '/');
      if(pathsep)
        *pathsep = 0;
    }


    pathsep = strchr(protsep, '/');
    if(pathsep)
      protsep = pathsep + 1;
    else
      protsep = NULL;


    if((useurl[0] == '.') && (useurl[1] == '/'))
      useurl += 2;

    while((useurl[0] == '.') &&
          (useurl[1] == '.') &&
          (useurl[2] == '/')) {
      level++;
      useurl += 3;
    }

    if(protsep) {
      while(level--) {

        pathsep = strrchr(protsep, '/');
        if(pathsep)
          *pathsep = 0;
        else {
          *protsep = 0;
          break;
        }
      }
    }
  }
  else {


    if(relurl[1] == '/') {


      *protsep = 0;
      useurl = &relurl[2];

      host_changed = TRUE;
    }
    else {


      pathsep = strchr(protsep, '/');
      if(pathsep) {


        char *sep = strchr(protsep, '?');
        if(sep && (sep < pathsep))
          pathsep = sep;
        *pathsep = 0;
      }
      else {


        pathsep = strchr(protsep, '?');
        if(pathsep)
          *pathsep = 0;
      }
    }
  }


  newlen = strlen_url(useurl, !host_changed);

  urllen = strlen(url_clone);

  newest = malloc(urllen + 1 +
                  newlen + 1 );

  if(!newest) {
    free(url_clone);
    return NULL;
  }


  memcpy(newest, url_clone, urllen);


  if(('/' == useurl[0]) || (protsep && !*protsep) || ('?' == useurl[0]))
    ;
  else
    newest[urllen++]='/';


  strcpy_url(&newest[urllen], useurl, !host_changed);

  free(url_clone);

  return newest;
}
