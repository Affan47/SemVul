single_domain(ares_channel channel, const char *name, char **s)
{
  size_t len = strlen(name);
  const char *hostaliases;
  FILE *fp;
  char *line = NULL;
  int status;
  size_t linesize;
  const char *p, *q;
  int error;


  if (name[len - 1] == '.')
    {
      *s = strdup(name);
      return (*s) ? ARES_SUCCESS : ARES_ENOMEM;
    }

  if (!(channel->flags & ARES_FLAG_NOALIASES) && !strchr(name, '.'))
    {

      hostaliases = getenv("HOSTALIASES");
      if (hostaliases)
        {
          fp = fopen(hostaliases, "r");
          if (fp)
            {
              while ((status = ares__read_line(fp, &line, &linesize))
                     == ARES_SUCCESS)
                {
                  if (strncasecmp(line, name, len) != 0 ||
                      !ISSPACE(line[len]))
                    continue;
                  p = line + len;
                  while (ISSPACE(*p))
                    p++;
                  if (*p)
                    {
                      q = p + 1;
                      while (*q && !ISSPACE(*q))
                        q++;
                      *s = malloc(q - p + 1);
                      if (*s)
                        {
                          memcpy(*s, p, q - p);
                          (*s)[q - p] = 0;
                        }
                      free(line);
                      fclose(fp);
                      return (*s) ? ARES_SUCCESS : ARES_ENOMEM;
                    }
                }
              free(line);
              fclose(fp);
              if (status != ARES_SUCCESS)
                return status;
            }
          else
            {
              error = errno;
              switch(error)
                {
                case ENOENT:
                case ESRCH:
                  break;
                default:
                  DEBUGF(fprintf(stderr, "fopen() failed with error: %d %s\n",
                                 error, strerror(error)));
                  DEBUGF(fprintf(stderr, "Error opening file: %s\n",
                                 hostaliases));
                  *s = NULL;
                  return ARES_EFILE;
                }
            }
        }
    }

  if (channel->flags & ARES_FLAG_NOSEARCH || channel->ndomains == 0)
    {

      *s = strdup(name);
      return (*s) ? ARES_SUCCESS : ARES_ENOMEM;
    }

  *s = NULL;
  return ARES_SUCCESS;
}
