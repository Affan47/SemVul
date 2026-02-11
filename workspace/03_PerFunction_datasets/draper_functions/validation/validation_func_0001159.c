open_score_file(char * mode)
{
  FILE * fi;


  fi = fopen("/var/games/circuslinux/scorefile", mode);

  if (fi == NULL)
    {
      fprintf(stderr, "\nWarning: I could not open the score file ");

      if (strcmp(mode, "r") == 0)
        fprintf(stderr, "for read:");
      else if (strcmp(mode, "w") == 0)
        fprintf(stderr, "for write:");

     fprintf(stderr, "\n%s\n"
              "The error that occured was:\n"
              "%s\n\n","/var/games/circuslinux/scorefile" , strerror(errno));
    }

  return(fi);
}
