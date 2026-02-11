fits_get_section_range(char **ptr,
                   long *secmin,
                   long *secmax,
                   long *incre,
                   int *status)


{
    int slen, isanumber;
    char token[FLEN_VALUE];

    if (*status > 0)
        return(*status);

    slen = fits_get_token(ptr, " ,:", token, &isanumber);


    if (slen==0) strcpy(token,"*");

    if (*token == '*')
    {
       *secmin = 1;
       *secmax = 0;
    }
    else if (*token == '-' && *(token+1) == '*' )
    {
       *secmin = 0;
       *secmax = 1;
    }
    else
    {
      if (slen == 0 || !isanumber || **ptr != ':')
        return(*status = URL_PARSE_ERROR);


      *secmin = atol(token);

      (*ptr)++;
      slen = fits_get_token(ptr, " ,:", token, &isanumber);

      if (slen == 0 || !isanumber)
        return(*status = URL_PARSE_ERROR);


      *secmax = atol(token);
    }

    if (**ptr == ':')
    {
        (*ptr)++;
        slen = fits_get_token(ptr, " ,", token, &isanumber);

        if (slen == 0 || !isanumber)
            return(*status = URL_PARSE_ERROR);

        *incre = atol(token);
    }
    else
        *incre = 1;

    if (**ptr == ',')
        (*ptr)++;

    while (**ptr == ' ')
         (*ptr)++;

    if (*secmin < 0 || *secmax < 0 || *incre < 1)
        *status = URL_PARSE_ERROR;

    return(*status);
}
