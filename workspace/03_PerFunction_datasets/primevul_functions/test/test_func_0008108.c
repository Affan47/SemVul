Curl_cookie_add(struct Curl_easy *data,


                struct CookieInfo *c,
                bool httpheader,
                bool noexpire,
                char *lineptr,
                const char *domain,
                const char *path,


                bool secure)
{
  struct Cookie *clist;
  struct Cookie *co;
  struct Cookie *lastc = NULL;
  struct Cookie *replace_co = NULL;
  struct Cookie *replace_clist = NULL;
  time_t now = time(NULL);
  bool replace_old = FALSE;
  bool badcookie = FALSE;
  size_t myhash;

#ifdef CURL_DISABLE_VERBOSE_STRINGS
  (void)data;
#endif

  DEBUGASSERT(MAX_SET_COOKIE_AMOUNT <= 255);
  if(data->req.setcookies >= MAX_SET_COOKIE_AMOUNT)
    return NULL;


  co = calloc(1, sizeof(struct Cookie));
  if(!co)
    return NULL;

  if(httpheader) {

    char name[MAX_NAME];
    char what[MAX_NAME];
    const char *ptr;
    const char *semiptr;

    size_t linelength = strlen(lineptr);
    if(linelength > MAX_COOKIE_LINE) {

      free(co);
      return NULL;
    }

    semiptr = strchr(lineptr, ';');

    while(*lineptr && ISBLANK(*lineptr))
      lineptr++;

    ptr = lineptr;
    do {

      name[0] = what[0] = 0;
      if(1 <= sscanf(ptr, "%" MAX_NAME_TXT "[^;\r\n=] =%"
                     MAX_NAME_TXT "[^;\r\n]",
                     name, what)) {


        const char *whatptr;
        bool done = FALSE;
        bool sep;
        size_t len = strlen(what);
        size_t nlen = strlen(name);
        const char *endofn = &ptr[ nlen ];


        if(nlen >= (MAX_NAME-1) || len >= (MAX_NAME-1) ||
           ((nlen + len) > MAX_NAME)) {
          freecookie(co);
          infof(data, "oversized cookie dropped, name/val %zu + %zu bytes",
                nlen, len);
          return NULL;
        }


        sep = (*endofn == '=')?TRUE:FALSE;

        if(nlen) {
          endofn--;
          if(ISBLANK(*endofn)) {

            while(*endofn && ISBLANK(*endofn) && nlen) {
              endofn--;
              nlen--;
            }
            name[nlen] = 0;
          }
        }


        while(len && ISBLANK(what[len-1])) {
          what[len-1] = 0;
          len--;
        }


        whatptr = what;
        while(*whatptr && ISBLANK(*whatptr))
          whatptr++;


        if(nlen > 3 && name[0] == '_' && name[1] == '_') {
          if(!strncmp("__Secure-", name, 9))
            co->prefix |= COOKIE_PREFIX__SECURE;
          else if(!strncmp("__Host-", name, 7))
            co->prefix |= COOKIE_PREFIX__HOST;
        }

        if(!co->name) {

          if(!sep) {

            badcookie = TRUE;
            break;
          }
          co->name = strdup(name);
          co->value = strdup(whatptr);
          done = TRUE;
          if(!co->name || !co->value) {
            badcookie = TRUE;
            break;
          }
          if(invalid_octets(whatptr) || invalid_octets(name)) {
            infof(data, "invalid octets in name/value, cookie dropped");
            badcookie = TRUE;
            break;
          }
        }
        else if(!len) {


          done = TRUE;


          if(strcasecompare("secure", name)) {
            if(secure || !c->running) {
              co->secure = TRUE;
            }
            else {
              badcookie = TRUE;
              break;
            }
          }
          else if(strcasecompare("httponly", name))
            co->httponly = TRUE;
          else if(sep)

            done = FALSE;
        }
        if(done)
          ;
        else if(strcasecompare("path", name)) {
          strstore(&co->path, whatptr);
          if(!co->path) {
            badcookie = TRUE;
            break;
          }
          free(co->spath);
          co->spath = sanitize_cookie_path(co->path);
          if(!co->spath) {
            badcookie = TRUE;
            break;
          }
        }
        else if(strcasecompare("domain", name) && whatptr[0]) {
          bool is_ip;


          if('.' == whatptr[0])
            whatptr++;

#ifndef USE_LIBPSL


          if(bad_domain(whatptr))
            domain = ":";
#endif

          is_ip = Curl_host_is_ipnum(domain ? domain : whatptr);

          if(!domain
             || (is_ip && !strcmp(whatptr, domain))
             || (!is_ip && tailmatch(whatptr, domain))) {
            strstore(&co->domain, whatptr);
            if(!co->domain) {
              badcookie = TRUE;
              break;
            }
            if(!is_ip)
              co->tailmatch = TRUE;

          }
          else {


            badcookie = TRUE;
            infof(data, "skipped cookie with bad tailmatch domain: %s",
                  whatptr);
          }
        }
        else if(strcasecompare("version", name)) {
          strstore(&co->version, whatptr);
          if(!co->version) {
            badcookie = TRUE;
            break;
          }
        }
        else if(strcasecompare("max-age", name)) {


          strstore(&co->maxage, whatptr);
          if(!co->maxage) {
            badcookie = TRUE;
            break;
          }
        }
        else if(strcasecompare("expires", name)) {
          strstore(&co->expirestr, whatptr);
          if(!co->expirestr) {
            badcookie = TRUE;
            break;
          }
        }


      }
      else {

      }

      if(!semiptr || !*semiptr) {

        semiptr = NULL;
        continue;
      }

      ptr = semiptr + 1;
      while(*ptr && ISBLANK(*ptr))
        ptr++;
      semiptr = strchr(ptr, ';');

      if(!semiptr && *ptr)


        semiptr = strchr(ptr, '\0');
    } while(semiptr);

    if(co->maxage) {
      CURLofft offt;
      offt = curlx_strtoofft((*co->maxage == '\"')?
                             &co->maxage[1]:&co->maxage[0], NULL, 10,
                             &co->expires);
      if(offt == CURL_OFFT_FLOW)

        co->expires = CURL_OFF_T_MAX;
      else if(!offt) {
        if(!co->expires)

          co->expires = 1;
        else if(CURL_OFF_T_MAX - now < co->expires)

          co->expires = CURL_OFF_T_MAX;
        else
          co->expires += now;
      }
    }
    else if(co->expirestr) {


      co->expires = Curl_getdate_capped(co->expirestr);


      if(co->expires == 0)
        co->expires = 1;
      else if(co->expires < 0)
        co->expires = 0;
    }

    if(!badcookie && !co->domain) {
      if(domain) {

        co->domain = strdup(domain);
        if(!co->domain)
          badcookie = TRUE;
      }
    }

    if(!badcookie && !co->path && path) {


      char *queryp = strchr(path, '?');


      char *endslash;
      if(!queryp)
        endslash = strrchr(path, '/');
      else
        endslash = memrchr(path, '/', (queryp - path));
      if(endslash) {
        size_t pathlen = (endslash-path + 1);
        co->path = malloc(pathlen + 1);
        if(co->path) {
          memcpy(co->path, path, pathlen);
          co->path[pathlen] = 0;
          co->spath = sanitize_cookie_path(co->path);
          if(!co->spath)
            badcookie = TRUE;
        }
        else
          badcookie = TRUE;
      }
    }


    if(badcookie || !co->name) {
      freecookie(co);
      return NULL;
    }
    data->req.setcookies++;
  }
  else {


    char *ptr;
    char *firstptr;
    char *tok_buf = NULL;
    int fields;


    if(strncmp(lineptr, "#HttpOnly_", 10) == 0) {
      lineptr += 10;
      co->httponly = TRUE;
    }

    if(lineptr[0]=='#') {

      free(co);
      return NULL;
    }

    ptr = strchr(lineptr, '\r');
    if(ptr)
      *ptr = 0;
    ptr = strchr(lineptr, '\n');
    if(ptr)
      *ptr = 0;

    firstptr = strtok_r(lineptr, "\t", &tok_buf);


    for(ptr = firstptr, fields = 0; ptr && !badcookie;
        ptr = strtok_r(NULL, "\t", &tok_buf), fields++) {
      switch(fields) {
      case 0:
        if(ptr[0]=='.')
          ptr++;
        co->domain = strdup(ptr);
        if(!co->domain)
          badcookie = TRUE;
        break;
      case 1:


        co->tailmatch = strcasecompare(ptr, "TRUE")?TRUE:FALSE;
        break;
      case 2:

        if(strcmp("TRUE", ptr) && strcmp("FALSE", ptr)) {

          co->path = strdup(ptr);
          if(!co->path)
            badcookie = TRUE;
          else {
            co->spath = sanitize_cookie_path(co->path);
            if(!co->spath) {
              badcookie = TRUE;
            }
          }
          break;
        }

        co->path = strdup("/");
        if(!co->path)
          badcookie = TRUE;
        co->spath = strdup("/");
        if(!co->spath)
          badcookie = TRUE;
        fields++;

      case 3:
        co->secure = FALSE;
        if(strcasecompare(ptr, "TRUE")) {
          if(secure || c->running)
            co->secure = TRUE;
          else
            badcookie = TRUE;
        }
        break;
      case 4:
        if(curlx_strtoofft(ptr, NULL, 10, &co->expires))
          badcookie = TRUE;
        break;
      case 5:
        co->name = strdup(ptr);
        if(!co->name)
          badcookie = TRUE;
        else {

          if(strncasecompare("__Secure-", co->name, 9))
            co->prefix |= COOKIE_PREFIX__SECURE;
          else if(strncasecompare("__Host-", co->name, 7))
            co->prefix |= COOKIE_PREFIX__HOST;
        }
        break;
      case 6:
        co->value = strdup(ptr);
        if(!co->value)
          badcookie = TRUE;
        break;
      }
    }
    if(6 == fields) {

      co->value = strdup("");
      if(!co->value)
        badcookie = TRUE;
      else
        fields++;
    }

    if(!badcookie && (7 != fields))

      badcookie = TRUE;

    if(badcookie) {
      freecookie(co);
      return NULL;
    }

  }

  if(co->prefix & COOKIE_PREFIX__SECURE) {

    if(!co->secure) {
      freecookie(co);
      return NULL;
    }
  }
  if(co->prefix & COOKIE_PREFIX__HOST) {


    if(co->secure && co->path && strcmp(co->path, "/") == 0 && !co->tailmatch)
      ;
    else {
      freecookie(co);
      return NULL;
    }
  }

  if(!c->running &&
     c->newsession &&
     !co->expires) {
    freecookie(co);
    return NULL;
  }

  co->livecookie = c->running;
  co->creationtime = ++c->lastct;


  if(!noexpire)
    remove_expired(c);

#ifdef USE_LIBPSL


  if(data && (domain && co->domain && !Curl_host_is_ipnum(co->domain))) {
    const psl_ctx_t *psl = Curl_psl_use(data);
    int acceptable;

    if(psl) {
      acceptable = psl_is_cookie_domain_acceptable(psl, domain, co->domain);
      Curl_psl_release(data);
    }
    else
      acceptable = !bad_domain(domain);

    if(!acceptable) {
      infof(data, "cookie '%s' dropped, domain '%s' must not "
                  "set cookies for '%s'", co->name, domain, co->domain);
      freecookie(co);
      return NULL;
    }
  }
#endif


  myhash = cookiehash(co->domain);
  clist = c->cookies[myhash];
  while(clist) {
    if(strcasecompare(clist->name, co->name)) {

      bool matching_domains = FALSE;

      if(clist->domain && co->domain) {
        if(strcasecompare(clist->domain, co->domain))

          matching_domains = TRUE;
      }
      else if(!clist->domain && !co->domain)
        matching_domains = TRUE;

      if(matching_domains &&
         clist->spath && co->spath &&
         clist->secure && !co->secure && !secure) {
        size_t cllen;
        const char *sep;


        sep = strchr(clist->spath + 1, '/');

        if(sep)
          cllen = sep - clist->spath;
        else
          cllen = strlen(clist->spath);

        if(strncasecompare(clist->spath, co->spath, cllen)) {
          infof(data, "cookie '%s' for domain '%s' dropped, would "
                "overlay an existing cookie", co->name, co->domain);
          freecookie(co);
          return NULL;
        }
      }
    }

    if(!replace_co && strcasecompare(clist->name, co->name)) {


      if(clist->domain && co->domain) {
        if(strcasecompare(clist->domain, co->domain) &&
          (clist->tailmatch == co->tailmatch))

          replace_old = TRUE;
      }
      else if(!clist->domain && !co->domain)
        replace_old = TRUE;

      if(replace_old) {


        if(clist->spath && co->spath) {
          if(strcasecompare(clist->spath, co->spath))
            replace_old = TRUE;
          else
            replace_old = FALSE;
        }
        else if(!clist->spath && !co->spath)
          replace_old = TRUE;
        else
          replace_old = FALSE;

      }

      if(replace_old && !co->livecookie && clist->livecookie) {


        freecookie(co);
        return NULL;
      }
      if(replace_old) {
        replace_co = co;
        replace_clist = clist;
      }
    }
    lastc = clist;
    clist = clist->next;
  }
  if(replace_co) {
    co = replace_co;
    clist = replace_clist;
    co->next = clist->next;


    co->creationtime = clist->creationtime;


    free(clist->name);
    free(clist->value);
    free(clist->domain);
    free(clist->path);
    free(clist->spath);
    free(clist->expirestr);
    free(clist->version);
    free(clist->maxage);

    *clist = *co;

    free(co);
    co = clist;
  }

  if(c->running)

    infof(data, "%s cookie %s=\"%s\" for domain %s, path %s, "
          "expire %" CURL_FORMAT_CURL_OFF_T,
          replace_old?"Replaced":"Added", co->name, co->value,
          co->domain, co->path, co->expires);

  if(!replace_old) {

    if(lastc)
      lastc->next = co;
    else
      c->cookies[myhash] = co;
    c->numcookies++;
  }


  if(co->expires && (co->expires < c->next_expiration))
    c->next_expiration = co->expires;

  return co;
}
