restore_chanban(struct chanset_t *chan, char *host)
{
  char *expi, *add, *last, *user, *desc;
  int flags = 0;

  expi = strchr_unescape(host, ':', '\\');
  if (expi) {
    if (*expi == '+') {
      flags |= MASKREC_PERM;
      expi++;
    }
    add = strchr(expi, ':');
    if (add) {
      if (add[-1] == '*') {
        flags |= MASKREC_STICKY;
        add[-1] = 0;
      } else
        *add = 0;
      add++;
      if (*add == '+') {
        last = strchr(add, ':');
        if (last) {
          *last = 0;
          last++;
          user = strchr(last, ':');
          if (user) {
            *user = 0;
            user++;
            desc = strchr(user, ':');
            if (desc) {
              *desc = 0;
              desc++;
              addmask_fully(chan, &chan->bans, &global_bans, host, user,
                            desc, atoi(expi), flags, atoi(add), atoi(last));
              return;
            }
          }
        }
      } else {
        desc = strchr(add, ':');
        if (desc) {
          *desc = 0;
          desc++;
          addmask_fully(chan, &chan->bans, &global_bans, host, add, desc,
                        atoi(expi), flags, now, 0);
          return;
        }
      }
    }
  }
  putlog(LOG_MISC, "*", "*** Malformed banline for %s.",
         chan ? chan->dname : "global_bans");
}
