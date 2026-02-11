ffpktp(fitsfile *fptr,
           const char *filename,
           int *status)


{
    FILE *diskfile;
    char card[FLEN_CARD], template[161];
    char keyname[FLEN_KEYWORD], newname[FLEN_KEYWORD];
    int keytype;
    size_t slen;

    if (*status > 0)
        return(*status);

    diskfile = fopen(filename,"r");
    if (!diskfile)
    {
            ffpmsg("ffpktp could not open the following template file:");
            ffpmsg(filename);
            return(*status = FILE_NOT_OPENED);
    }

    while (fgets(template, 160, diskfile) )
    {
      template[160] = '\0';
      slen = strlen(template);
      template[slen - 1] = '\0';

      if (ffgthd(template, card, &keytype, status) > 0)
         break;

      strncpy(keyname, card, 8);
      keyname[8] = '\0';

      if (keytype == -2)
      {
         strncpy(newname, &card[40], 8);
         newname[8] = '\0';

         ffmnam(fptr, keyname, newname, status);
      }
      else if (keytype == -1)
      {
         ffdkey(fptr, keyname, status);
      }
      else if (keytype == 0)
      {
         ffucrd(fptr, keyname, card, status);
      }
      else if (keytype == 1)
      {
         ffprec(fptr, card, status);
      }
      else
      {
         break;
      }
    }

    fclose(diskfile);
    return(*status);
}
