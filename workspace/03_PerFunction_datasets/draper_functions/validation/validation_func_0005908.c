copyFile(char *from, char *to)
{
    int         num_read;
    char        buf[HE_BUF_SZ];
    FILE       *fp;
    FILE       *bfp;


    if ((fp = fopen(from, "r")) == NULL)
      {
          fprintf(stderr, "Unable to open file: <%s>\n", from);
          return FAIL;
      }
    if ((bfp = fopen(to, "w")) == NULL)
      {
          fclose(fp);
          fprintf(stderr, "Unable to open backup file.\n");
          return FAIL;
      }

    while ((num_read = (int)fread(buf, 1, HE_BUF_SZ, fp)) > 0)
        fwrite(buf, 1, (size_t)num_read, bfp);

    fclose(fp);
    fclose(bfp);

    return HE_OK;
}
