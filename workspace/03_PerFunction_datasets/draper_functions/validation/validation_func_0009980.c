changeinmemberlist_mode(channel_t *c, const char *nick, char mode, int add)
{
  member_t *member;
  int pi;

  updatecontext();

  if (gdata.debug > 2)
    {
      ioutput(CALLTYPE_NORMAL, OUT_S, COLOR_NO_COLOR,
              "%s prefix %c on %s in %s",
              add ? "adding" : "removing",
              mode, nick, c->name);
    }


  member = irlist_get_head(&c->members);
  while(member)
    {
      if (!strcasecmp(member->nick,nick))
        {
          break;
        }
      member = irlist_get_next(member);
    }

  if (member)
    {
      if (add)
        {
          for (pi = 0;
               (pi < MAX_PREFIX && member->prefixes[pi] && member->prefixes[pi] != mode);
               pi++) ;
          if (pi < MAX_PREFIX)
            {
              member->prefixes[pi] = mode;
            }
        }
      else
        {
          for (pi = 0; (pi < MAX_PREFIX && member->prefixes[pi]); pi++)
            {
              if (member->prefixes[pi] == mode)
                {
                  for (pi++; pi < MAX_PREFIX; pi++)
                    {
                      member->prefixes[pi-1] = member->prefixes[pi];
                    }
                  member->prefixes[MAX_PREFIX-1] = '\0';
                  break;
                }
            }
        }

    }

  return;
}
