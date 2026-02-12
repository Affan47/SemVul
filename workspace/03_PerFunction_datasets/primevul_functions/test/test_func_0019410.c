void progressbarinit(struct ProgressData *bar,
                     struct Configurable *config)
{
#ifdef __EMX__

  int scr_size [2];
#endif
  char *colp;

  memset(bar, 0, sizeof(struct ProgressData));


  if (config->use_resume)
    bar->initial_size = config->resume_from;


#ifndef __EMX__


  colp = curlx_getenv("COLUMNS");
  if (colp != NULL) {
    bar->width = atoi(colp);
    curl_free(colp);
  }
  else
    bar->width = 79;
#else


  _scrsize(scr_size);
  bar->width = scr_size[0] - 1;
#endif

  bar->out = config->errors;
}
