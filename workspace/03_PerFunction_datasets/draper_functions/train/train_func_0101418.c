vt_env_stat_props()
{
  static int propflags = 0;
  char* tmp;

  if (propflags == 0)
    {
      tmp = getenv("VT_STAT_PROPS");
      if (tmp != NULL && strlen(tmp) > 0)
        {
          char tmpbuf[128];
          char* p;
          char* tk;
          int dc;

          vt_cntl_msg(2, "VT_STAT_PROPS=%s", tmp);

          p = tmpbuf;
          strncpy(tmpbuf, tmp, 127);
          tmpbuf[127] = '\0';
          while( *p ) { *p = tolower(*p); p++; }

          if (strcmp( tmpbuf, "all" ) == 0)
            {
              propflags = (VT_SUM_PROP_FUNC | VT_SUM_PROP_MSG | VT_SUM_PROP_COLLOP);
            }
          else
            {
              tk = strtok(tmpbuf, ":");
              dc = 0;
              propflags = 0;
              do {
                if (dc <= 2 &&
                    (strcmp( tk, "func" ) == 0))
                  propflags |= VT_SUM_PROP_FUNC;
                else if(dc <= 2 &&
                        (strcmp( tk, "msg" ) == 0))
                  propflags |= VT_SUM_PROP_MSG;
                else if(dc <= 2 &&
                        (strcmp( tk, "collop" ) == 0))
                  propflags |= VT_SUM_PROP_COLLOP;


                else
                  vt_error_msg("VT_STAT_PROPS not properly set");
                dc++;
              } while((tk = strtok(0, ":")));
            }
        }
      else
        {


          propflags = (VT_SUM_PROP_FUNC | VT_SUM_PROP_MSG | VT_SUM_PROP_COLLOP);
        }
    }
  return propflags;
}
