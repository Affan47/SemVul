static int parseconfig(const char *filename,
                       struct Configurable *config)
{
  int res;
  FILE *file;
  char filebuffer[512];
  bool usedarg;
  char *home;

  if(!filename || !*filename) {


#define CURLRC DOT_CHAR "curlrc"

#ifndef __AMIGA__
    filename = CURLRC;
    home = homedir();
    if(home) {
      if(strlen(home)<(sizeof(filebuffer)-strlen(CURLRC))) {
        snprintf(filebuffer, sizeof(filebuffer),
                 "%s%s%s", home, DIR_CHAR, CURLRC);

#ifdef WIN32


        file = fopen(filebuffer, "r");
        if (file != NULL) {
          fclose(file);
          filename = filebuffer;
        }
        else {


          int n = GetModuleFileName(0, filebuffer, sizeof(filebuffer));
          if (n > 0 && n < (int)sizeof(filebuffer)) {

            char *lastdirchar = strrchr(filebuffer, '\\');
            if (lastdirchar) {
              int remaining;
              *lastdirchar = 0;

              remaining = sizeof(filebuffer) - strlen(filebuffer);
              if ((int)strlen(CURLRC) < remaining - 1) {
                snprintf(lastdirchar, remaining,
                         "%s%s", DIR_CHAR, CURLRC);


                filename = filebuffer;
              }
            }
          }
        }
#else
        filename = filebuffer;
#endif
      }
      free(home);
    }

# else


  filename = "ENV:" CURLRC;

#endif
  }

  if(strcmp(filename,"-"))
    file = fopen(filename, "r");
  else
    file = stdin;

  if(file) {
    char *line;
    char *aline;
    char *option;
    char *param;
    int lineno=0;
    bool alloced_param;

#define ISSEP(x) (((x)=='=') || ((x) == ':'))

    while (NULL != (aline = my_get_line(file))) {
      lineno++;
      line = aline;
      alloced_param=FALSE;


      while(*line && ISSPACE(*line))
        line++;

      switch(*line) {
      case '#':
      case '/':
      case '\r':
      case '\n':
      case '*':
      case '\0':
        free(aline);
        continue;
      }


      option = line;
      while(*line && !ISSPACE(*line) && !ISSEP(*line))
        line++;


      if(*line)
        *line++=0;

#ifdef DEBUG_CONFIG
      fprintf(stderr, "GOT: %s\n", option);
#endif


      while(*line && (ISSPACE(*line) || ISSEP(*line)))
        line++;


      if(*line == '\"') {
        char *ptr;

        line++;
        param=strdup(line);
        alloced_param=TRUE;

        ptr=param;
        while(*line && (*line != '\"')) {
          if(*line == '\\') {
            char out;
            line++;


            switch(out = *line) {
            case '\0':
              continue;
            case 't':
              out='\t';
              break;
            case 'n':
              out='\n';
              break;
            case 'r':
              out='\r';
              break;
            case 'v':
              out='\v';
              break;
            }
            *ptr++=out;
            line++;
          }
          else
            *ptr++=*line++;
        }
        *ptr=0;

      }
      else {
        param=line;
        while(*line && !ISSPACE(*line))
          line++;
        *line=0;
      }

      if (param && !*param) {


        if (alloced_param)
          free(param);
        param = NULL;
      }

#ifdef DEBUG_CONFIG
      fprintf(stderr, "PARAM: \"%s\"\n",(param ? param : "(null)"));
#endif
      res = getparameter(option, param, &usedarg, config);

      if (param && *param && !usedarg)

        res = PARAM_GOT_EXTRA_PARAMETER;

      if(res != PARAM_OK) {

        if(!strcmp(filename, "-")) {
          filename=(char *)"<stdin>";
        }
        if(PARAM_HELP_REQUESTED != res) {
          const char *reason = param2text(res);
          warnf(config, "%s:%d: warning: '%s' %s\n",
                filename, lineno, option, reason);
        }
      }

      if(alloced_param)
      {
        free(param);
        param = NULL;
      }

      free(aline);
    }
    if(file != stdin)
      fclose(file);
  }
  else
    return 1;
  return 0;
}
