struct Cookie *Curl_cookie_getlist(struct Curl_easy *data,
                                   struct CookieInfo *c,
                                   const char *host, const char *path,
                                   bool secure)
{
  struct Cookie *newco;
  struct Cookie *co;
  struct Cookie *mainco = NULL;
  size_t matches = 0;
  bool is_ip;
  const size_t myhash = cookiehash(host);

  if(!c || !c->cookies[myhash])
    return NULL;


  remove_expired(c);


  is_ip = Curl_host_is_ipnum(host);

  co = c->cookies[myhash];

  while(co) {

    if(co->secure?secure:TRUE) {


      if(!co->domain ||
         (co->tailmatch && !is_ip && tailmatch(co->domain, host)) ||
         ((!co->tailmatch || is_ip) && strcasecompare(host, co->domain)) ) {


        if(!co->spath || pathmatch(co->spath, path) ) {


          newco = dup_cookie(co);
          if(newco) {

            newco->next = mainco;


            mainco = newco;

            matches++;
            if(matches >= MAX_COOKIE_SEND_AMOUNT) {
              infof(data, "Included max number of cookies (%zu) in request!",
                    matches);
              break;
            }
          }
          else
            goto fail;
        }
      }
    }
    co = co->next;
  }

  if(matches) {


    struct Cookie **array;
    size_t i;


    array = malloc(sizeof(struct Cookie *) * matches);
    if(!array)
      goto fail;

    co = mainco;

    for(i = 0; co; co = co->next)
      array[i++] = co;


    qsort(array, matches, sizeof(struct Cookie *), cookie_sort);


    mainco = array[0];
    for(i = 0; i<matches-1; i++)
      array[i]->next = array[i + 1];
    array[matches-1]->next = NULL;

    free(array);
  }

  return mainco;

fail:

  Curl_cookie_freelist(mainco);
  return NULL;
}
